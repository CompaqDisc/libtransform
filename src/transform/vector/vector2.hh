#pragma once

#include <memory>

#include <transform/vector/vector.hh>

namespace transform
{
	template <class T>
	class Vector2 : public Vector<2, T>
	{
	private:
		typedef Vector<2, T> super;

	public:
		Vector2() : super() {}							// default construct
		Vector2(const T x, const T y);					// member construct
		Vector2(const Vector2<T>& v) : super(v) {}		// copy construct
		Vector2(const Vector<2, T>& v) : super(v) {}	// copy construct from superclass

		template <class U>
		Vector2(const Vector2<U>& v)	// convert construct
		{
			this->_v[0] = v[0];
			this->_v[1] = v[1];
		}

		template <class U>
		Vector2(const Vector<2, U>& v)	// convert construct
		{
			this->_v[0] = v[0];
			this->_v[1] = v[1];
		}

		// members
		T& x = this->_v[0];
		T& y = this->_v[1];

		T& u = this->_v[0];
		T& v = this->_v[1];

		// utility
		Vector2<T>& set(const T x, const T y);

		// math
		const T cross(const Vector2<T>&) const;
	};
}

using transform::Vector2;

template <class T>
Vector2<T>::Vector2(T x, T y)
{
	this->_v[0] = x;
	this->_v[1] = y;
}

template <class T>
Vector2<T>& Vector2<T>::set(const T x, const T y)
{
	this->_v[0] = x;
	this->_v[1] = y;
	return *this;
}

// In 2d, the value is the magnitude of the z-axis.
// See `https://allenchou.net/2013/07/cross-product-of-2d-vectors/` for further reading.
template <class T>
inline const T Vector2<T>::cross(const Vector2<T>& v) const
{
	return x * v.y - y * v.x;
}
