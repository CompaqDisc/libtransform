#pragma once

#include <memory>

namespace transform
{
	// typename std::enable_if<std::is_arithmetic<T>::value>
    template <class T>
    class Vector3
	{
	protected:
		T _v[3];

    public:
		// constructors
        Vector3() = default;						// default construct
        Vector3(const T x, const T y, const T z);	// member construct
		Vector3(const Vector3<T>& v);				// copy construct

		template <class U>
		Vector3(const Vector3<U>& v)				// convert construct
		{
			_v[0] = v[0];
			_v[1] = v[1];
			_v[2] = v[2];
		}

		// members
		T& x = _v[0];
		T& y = _v[1];
		T& z = _v[2];

		T& r = _v[0];
		T& g = _v[1];
		T& b = _v[2];

		// utility
		Vector3<T>& zero();
		Vector3<T>& set(const T x, const T y, const T z);
		Vector3<T>& normalize();

		// math
		const T mag() const;
		const T sum() const;
		const T dot(const Vector3<T>&) const;
		const Vector3<T> project(const Vector3<T>&) const;
		const Vector3<T> reject(const Vector3<T>&) const;
		const Vector3<T> cross() const;
		const Vector3<T> abs() const;

		// operators
		Vector3<T>& operator=(const Vector3<T>&);				// assignment

		const T operator[] (const size_t i) const;				// indexing
		T& operator[] (const size_t i);							// indexing

		const Vector3<T> operator-();							// unary negatation

		Vector3<T>& operator*=(const T);						// scalar multiplication
		Vector3<T>& operator/=(const T);						// scalar division

		Vector3<T>& operator+=(const Vector3<T>&);				// vector addition
		Vector3<T>& operator-=(const Vector3<T>&);				// vector subtraction
		Vector3<T>& operator*=(const Vector3<T>&);				// element-wise multiplication
		Vector3<T>& operator/=(const Vector3<T>&);				// element-wise division

		const Vector3<T> operator<(const T);					// compare each element with s, return vector of 1s and 0s
		const Vector3<T> operator>(const T);

		const Vector3<T> operator<(const Vector3&);				// element-wise comparison, return vector of 1s and 0s
		const Vector3<T> operator>(const Vector3&);

		bool operator==(const Vector3<T>&);						// equality
		bool operator!=(const Vector3<T>&);						// inequality

		T* ptr() { return _v; }
    };

	template <class T>
	Vector3<T> operator*(Vector3<T>, const T);				// scalar multiplication
	template <class T>
	Vector3<T> operator/(Vector3<T>, const T);				// scalar division

	template <class T>
	Vector3<T> operator+(Vector3<T>, const Vector3<T>&);	// vector addition
	template <class T>
	Vector3<T> operator-(Vector3<T>, const Vector3<T>&);	// vector subtraction
	template <class T>
	Vector3<T> operator*(Vector3<T>, const Vector3<T>&);	// element-wise multiplication
	template <class T>
	Vector3<T> operator/(Vector3<T>, const Vector3<T>&);	// element-wise division
}

using transform::Vector3;

template <class T>
Vector3<T>::Vector3(T x, T y, T z)
{
	_v[0] = x;
	_v[1] = y;
	_v[2] = z;
}

template <class T>
Vector3<T>::Vector3(const Vector3<T>& v)
{
	_v[0] = v[0];
	_v[1] = v[1];
	_v[2] = v[2];
}

template <class T>
Vector3<T>& Vector3<T>::zero()
{
	_v[0] = 0.0;
	_v[1] = 0.0;
	_v[2] = 0.0;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::set(const T x, const T y, const T z)
{
	_v[0] = x;
	_v[1] = y;
	_v[2] = z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::normalize()
{
	T n = mag();
	if (n) {
		x /= n;
		y /= n;
		z /= n;
	}
	return *this;
}

// https://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm
// Aka length or magnitude.
template <class T>
inline const T Vector3<T>::mag() const
{
	return (T) sqrt(dot(*this));
}

template <class T>
inline const T Vector3<T>::sum() const
{
	return x + y + z;
}

template <class T>
inline const T Vector3<T>::dot(const Vector3<T>& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

template <class T>
inline const Vector3<T> Vector3<T>::project(const Vector3<T>& v) const
{
	return (v * (this->dot(v) / v.dot(v)));
}

template <class T>
inline const Vector3<T> Vector3<T>::reject(const Vector3<T>& v) const
{
	return (*this - this->project(v));
}

template <class T>
inline const T Vector3<T>::operator[](const size_t i) const
{
	return _v[i%3];
}

template <class T>
T& Vector3<T>::operator[](const size_t i)
{
	return _v[i%3];
}

template <class T>
inline const Vector3<T> Vector3<T>::operator-()
{
	return Vector3<T>(-x, -y, -z);
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(const T s)
{
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator/=(const T s)
{
	x /= s;
	y /= s;
	z /= s;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator+=(const Vector3<T>& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator-=(const Vector3<T>& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator*=(const Vector3<T>& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

template <class T>
Vector3<T>& Vector3<T>::operator/=(const Vector3<T>& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

template <class T>
inline const Vector3<T> Vector3<T>::operator<(const T s) {
	return Vector3<T>(_v[0] < s, _v[1] < s, _v[2] < s);
}

template <class T>
inline const Vector3<T> Vector3<T>::operator>(const T s) {
	return Vector3<T>(_v[0] > s, _v[1] > s, _v[2] > s);
}

template <class T>
inline const Vector3<T> Vector3<T>::operator<(const Vector3<T>& v) {
	return Vector3<T>(_v[0] < v[0], _v[1] < v[1], _v[2] < v[2]);
}

template <class T>
inline const Vector3<T> Vector3<T>::operator>(const Vector3<T>& v) {
	return Vector3<T>(_v[0] > v[0], _v[1] > v[1], _v[2] > v[2]);
}

template <class T>
inline bool Vector3<T>::operator==(const Vector3<T>& v) {
	return _v[0] == v[0] && _v[1] == v[1] && _v[2] == v[2];
}

template <class T>
inline bool Vector3<T>::operator!=(const Vector3<T>& v) {
	return !(*this == v);
}

template <class T>
inline Vector3<T> transform::operator*(Vector3<T> v, const T s)
{
	v *= s;
	return v;
}

template <class T>
inline Vector3<T> transform::operator/(Vector3<T> v, const T s)
{
	v /= s;
	return v;
}

template <class T>
inline Vector3<T> transform::operator+(Vector3<T> v1, const Vector3<T>& v2)
{
	v1 += v2;
	return v1;
}

template <class T>
inline Vector3<T> transform::operator-(Vector3<T> v1, const Vector3<T>& v2)
{
	v1 -= v2;
	return v1;
}

template <class T>
inline Vector3<T> transform::operator*(Vector3<T> v1, const Vector3<T>& v2)
{
	v1 *= v2;
	return v1;
}

template <class T>
inline Vector3<T> transform::operator/(Vector3<T> v1, const Vector3<T>& v2)
{
	v1 /= v2;
	return v1;
}