#pragma once

#include <memory>

#include "vector.hh"

namespace transform
{
	template <class T>
	class Vector3 : public Vector<3, T>
	{
	private:
		typedef Vector<3, T> super;

	public:
		Vector3() : super() {}							// default construct
		Vector3(const T x, const T y, const T z);		// member construct
		Vector3(const Vector3<T>& v) : super(v) {}		// copy construct
		Vector3(const Vector<3, T>& v) : super(v) {}	// copy construct from superclass

		template <class U>
		Vector3(const Vector3<U>& v)	// convert construct
		{
			this->_v[0] = v[0];
			this->_v[1] = v[1];
			this->_v[2] = v[2];
		}

		template <class U>
		Vector3(const Vector<3, U>& v)	// convert construct
		{
			this->_v[0] = v[0];
			this->_v[1] = v[1];
			this->_v[2] = v[2];
		}

		// members
		T& x = this->_v[0];
		T& y = this->_v[1];
		T& z = this->_v[2];

		T& r = this->_v[0];
		T& g = this->_v[1];
		T& b = this->_v[2];

		// utility
		Vector3<T>& set(const T x, const T y, const T z);

		// math
		const Vector3<T> cross(const Vector3<T>& v) const;
	};
}

using transform::Vector3;

template <class T>
Vector3<T>::Vector3(T x, T y, T z)
{
	this->_v[0] = x;
	this->_v[1] = y;
	this->_v[2] = z;
}

template <class T>
Vector3<T>& Vector3<T>::set(const T x, const T y, const T z)
{
	this->_v[0] = x;
	this->_v[1] = y;
	this->_v[2] = z;
	return *this;
}

template <class T>
inline const Vector3<T> Vector3<T>::cross(const Vector3<T>& v) const
{
	return Vector3<T>(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}
