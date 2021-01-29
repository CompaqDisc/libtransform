#pragma once

#include <memory>

#include "vector.hh"

namespace transform
{
	template <class T>
	class Vector4 : public Vector<4, T>
	{
	private:
		typedef Vector<4, T> super;

	public:
		Vector4() : super() {}									// default construct
		Vector4(const T x, const T y, const T z, const T w);	// member construct
		Vector4(const Vector4<T>& v) : super(v) {}				// copy construct
		Vector4(const Vector<4, T>& v) : super(v) {}			// copy construct from superclass

		template <class U>
		Vector4(const Vector4<U>& v)	// convert construct
		{
			this->_v[0] = v[0];
			this->_v[1] = v[1];
			this->_v[2] = v[2];
			this->_v[3] = v[3];
		}

		template <class U>
		Vector4(const Vector<4, U>& v)	// convert construct
		{
			this->_v[0] = v[0];
			this->_v[1] = v[1];
			this->_v[2] = v[2];
			this->_v[3] = v[3];
		}

		// members
		T& x = this->_v[0];
		T& y = this->_v[1];
		T& z = this->_v[2];
		T& w = this->_v[3];

		T& r = this->_v[0];
		T& g = this->_v[1];
		T& b = this->_v[2];
		T& a = this->_v[3];

		// utility
		Vector4<T>& set(const T x, const T y, const T z, const T w);
	};
}

using transform::Vector4;

template <class T>
Vector4<T>::Vector4(T x, T y, T z, T w)
{
	this->_v[0] = x;
	this->_v[1] = y;
	this->_v[2] = z;
	this->_v[3] = w;
}

template <class T>
Vector4<T>& Vector4<T>::set(const T x, const T y, const T z, const T w)
{
	this->_v[0] = x;
	this->_v[1] = y;
	this->_v[2] = z;
	this->_v[3] = w;
	return *this;
}
