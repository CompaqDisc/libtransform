#pragma once

#include <memory>

namespace transform
{
	// typename std::enable_if<std::is_arithmetic<T>::value>
    template <class T>
    class Vector2
	{
	protected:
		T _v[2];

    public:
		// constructors
        Vector2() = default;			// default construct
        Vector2(const T x, const T y);	// member construct
		Vector2(const Vector2<T>& v);	// copy construct

		template <class U>
		Vector2(const Vector2<U>& v)	// convert construct
		{
			_v[0] = v[0];
			_v[1] = v[1];
		}

		// members
		T& x = _v[0];
		T& y = _v[1];

		T& u = _v[0];
		T& v = _v[1];

		// utility
		Vector2<T>& zero();
		Vector2<T>& set(const T x, const T y);
		Vector2<T>& normalize();

		// math
		const T mag() const;
		const T sum() const;
		const T dot(const Vector2<T>&) const;
		const Vector2<T> project(const Vector2<T>&) const;
		const Vector2<T> reject(const Vector2<T>&) const;
		const Vector2<T> cross() const;
		const Vector2<T> abs() const;

		// operators
		Vector2<T>& operator=(const Vector2<T>&);				// assignment

		const T operator[] (const size_t i) const;				// indexing
		T& operator[] (const size_t i);							// indexing

		const Vector2<T> operator-();							// unary negatation

		Vector2<T>& operator*=(const T);						// scalar multiplication
		Vector2<T>& operator/=(const T);						// scalar division

		Vector2<T>& operator+=(const Vector2<T>&);				// vector addition
		Vector2<T>& operator-=(const Vector2<T>&);				// vector subtraction
		Vector2<T>& operator*=(const Vector2<T>&);				// element-wise multiplication
		Vector2<T>& operator/=(const Vector2<T>&);				// element-wise division

		const Vector2<T> operator<(const T);					// compare each element with s, return vector of 1s and 0s
		const Vector2<T> operator>(const T);

		const Vector2<T> operator<(const Vector2&);				// element-wise comparison, return vector of 1s and 0s
		const Vector2<T> operator>(const Vector2&);

		bool operator==(const Vector2<T>&);						// equality
		bool operator!=(const Vector2<T>&);						// inequality

		T* ptr() { return _v; }
    };

	template <class T>
	Vector2<T> operator*(Vector2<T>, const T);				// scalar multiplication
	template <class T>
	Vector2<T> operator/(Vector2<T>, const T);				// scalar division

	template <class T>
	Vector2<T> operator+(Vector2<T>, const Vector2<T>&);	// vector addition
	template <class T>
	Vector2<T> operator-(Vector2<T>, const Vector2<T>&);	// vector subtraction
	template <class T>
	Vector2<T> operator*(Vector2<T>, const Vector2<T>&);	// element-wise multiplication
	template <class T>
	Vector2<T> operator/(Vector2<T>, const Vector2<T>&);	// element-wise division
}

using transform::Vector2;

template <class T>
Vector2<T>::Vector2(T x, T y)
{
	_v[0] = x;
	_v[1] = y;
}

template <class T>
Vector2<T>::Vector2(const Vector2<T>& v)
{
	_v[0] = v[0];
	_v[1] = v[1];
}

template <class T>
Vector2<T>& Vector2<T>::zero()
{
	_v[0] = 0.0;
	_v[1] = 0.0;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::set(const T x, const T y)
{
	_v[0] = x;
	_v[1] = y;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::normalize()
{
	T n = mag();
	if (n) {
		x /= n;
		y /= n;
	}
	return *this;
}

// https://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm
// Aka length or magnitude.
template <class T>
inline const T Vector2<T>::mag() const
{
	return (T) sqrt(dot(*this));
}

template <class T>
inline const T Vector2<T>::sum() const
{
	return x + y;
}

template <class T>
inline const T Vector2<T>::dot(const Vector2<T>& v) const
{
	return x * v.x + y * v.y;
}

template <class T>
inline const Vector2<T> Vector2<T>::project(const Vector2<T>& v) const
{
	return (v * (this->dot(v) / v.dot(v)));
}

template <class T>
inline const Vector2<T> Vector2<T>::reject(const Vector2<T>& v) const
{
	return (*this - this->project(v));
}

template <class T>
inline const T Vector2<T>::operator[](const size_t i) const
{
	return _v[i%2];
}

template <class T>
T& Vector2<T>::operator[](const size_t i)
{
	return _v[i%2];
}

template <class T>
inline const Vector2<T> Vector2<T>::operator-()
{
	return Vector2<T>(-x, -y);
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(const T s)
{
	x *= s;
	y *= s;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator/=(const T s)
{
	x /= s;
	y /= s;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator*=(const Vector2<T>& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

template <class T>
Vector2<T>& Vector2<T>::operator/=(const Vector2<T>& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

template <class T>
inline const Vector2<T> Vector2<T>::operator<(const T s) {
	return Vector2<T>(_v[0] < s, _v[1] < s);
}

template <class T>
inline const Vector2<T> Vector2<T>::operator>(const T s) {
	return Vector2<T>(_v[0] > s, _v[1] > s);
}

template <class T>
inline const Vector2<T> Vector2<T>::operator<(const Vector2<T>& v) {
	return Vector2<T>(_v[0] < v[0], _v[1] < v[1]);
}

template <class T>
inline const Vector2<T> Vector2<T>::operator>(const Vector2<T>& v) {
	return Vector2<T>(_v[0] > v[0], _v[1] > v[1]);
}

template <class T>
inline bool Vector2<T>::operator==(const Vector2<T>& v) {
	return _v[0] == v[0] && _v[1] == v[1];
}

template <class T>
inline bool Vector2<T>::operator!=(const Vector2<T>& v) {
	return !(*this == v);
}

template <class T>
inline Vector2<T> transform::operator*(Vector2<T> v, const T s)
{
	v *= s;
	return v;
}

template <class T>
inline Vector2<T> transform::operator/(Vector2<T> v, const T s)
{
	v /= s;
	return v;
}

template <class T>
inline Vector2<T> transform::operator+(Vector2<T> v1, const Vector2<T>& v2)
{
	v1 += v2;
	return v1;
}

template <class T>
inline Vector2<T> transform::operator-(Vector2<T> v1, const Vector2<T>& v2)
{
	v1 -= v2;
	return v1;
}

template <class T>
inline Vector2<T> transform::operator*(Vector2<T> v1, const Vector2<T>& v2)
{
	v1 *= v2;
	return v1;
}

template <class T>
inline Vector2<T> transform::operator/(Vector2<T> v1, const Vector2<T>& v2)
{
	v1 /= v2;
	return v1;
}