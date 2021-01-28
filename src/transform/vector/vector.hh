#pragma once

#include <memory>

namespace transform
{
	// typename std::enable_if<std::is_arithmetic<T>::value>
	template <int N, class T>
	class Vector
	{
	protected:
		T _v[N];

	public:
		// constructors
		Vector() = default;				// default construct
		Vector(const Vector<N, T>& v);	// copy construct

		// utility
		Vector<N, T>& zero();
		Vector<N, T>& normalize();

		// math
		const T mag() const;
		const T length() const;
		const T length2() const;
		const T sum() const;
		const T dot(const Vector<N, T>&) const;
		const Vector<N, T> project(const Vector<N, T>&) const;
		const Vector<N, T> reject(const Vector<N, T>&) const;
		const Vector<N, T> abs() const;

		// operators
		Vector<N, T>& operator=(const Vector<N, T>&);		// assignment

		const T operator[] (const size_t i) const;			// indexing
		T& operator[] (const size_t i);						// indexing

		const Vector<N, T> operator-();						// unary negatation

		Vector<N, T>& operator*=(const T);					// scalar multiplication
		Vector<N, T>& operator/=(const T);					// scalar division

		Vector<N, T>& operator+=(const Vector<N, T>&);		// vector addition
		Vector<N, T>& operator-=(const Vector<N, T>&);		// vector subtraction
		Vector<N, T>& operator*=(const Vector<N, T>&);		// element-wise multiplication
		Vector<N, T>& operator/=(const Vector<N, T>&);		// element-wise division

		const Vector<N, T> operator<(const T);				// compare each element with s, return vector of 1s and 0s
		const Vector<N, T> operator>(const T);

		const Vector<N, T> operator<(const Vector<N, T>&);	// element-wise comparison, return vector of 1s and 0s
		const Vector<N, T> operator>(const Vector<N, T>&);

		bool operator==(const Vector<N, T>&);				// equality
		bool operator!=(const Vector<N, T>&);				// inequality

		T* ptr() { return _v; }
	};

	template <int N, class T>
	Vector<N, T> operator*(Vector<N, T>, const T);	// scalar multiplication
	template <int N, class T>
	Vector<N, T> operator/(Vector<N, T>, const T);	// scalar division

	template <int N, class T>
	Vector<N, T> operator+(Vector<N, T>, const Vector<N, T>&);	// vector addition
	template <int N, class T>
	Vector<N, T> operator-(Vector<N, T>, const Vector<N, T>&);	// vector subtraction
	template <int N, class T>
	Vector<N, T> operator*(Vector<N, T>, const Vector<N, T>&);	// element-wise multiplication
	template <int N, class T>
	Vector<N, T> operator/(Vector<N, T>, const Vector<N, T>&);	// element-wise division
}

using transform::Vector;

template <int N, class T>
Vector<N, T>::Vector(const Vector<N, T>& v)
{
	for (int i = 0; i < N; i++) { _v[i] = v[i]; }
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::zero()
{
	for (int i = 0; i < N; i++) { _v[i] = 0.0; }
	return *this;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::normalize()
{
	T n = mag();
	if (n) {
		for (int i = 0; i < N; i++) { _v[i] /= n; }
	}
	return *this;
}

// https://en.wikipedia.org/wiki/Norm_(mathematics)#Euclidean_norm
// Aka length or magnitude.
template <int N, class T>
inline const T Vector<N, T>::mag() const
{
	return (T) sqrt(dot(*this));
}

// Alias of above
template <int N, class T>
inline const T Vector<N, T>::length() const
{
	return (T) sqrt(dot(*this));
}

// Skips a costly sqrt
template <int N, class T>
inline const T Vector<N, T>::length2() const
{
	return (T) dot(*this);
}

template <int N, class T>
inline const T Vector<N, T>::sum() const
{
	T result = 0.0;
	for (int i = 0; i < N; i++) { result += _v[i]; }
	return result;
}

template <int N, class T>
inline const T Vector<N, T>::dot(const Vector<N, T>& v) const
{
	T result = 0.0;
	for (int i = 0; i < N; i++) { result += _v[i] * v[i]; }
	return result;
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::project(const Vector<N, T>& v) const
{
	return (v * (this->dot(v) / v.dot(v)));
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::reject(const Vector<N, T>& v) const
{
	return (*this - this->project(v));
}

template <int N, class T>
inline const T Vector<N, T>::operator[](const size_t i) const
{
	return _v[i%N];
}

template <int N, class T>
T& Vector<N, T>::operator[](const size_t i)
{
	return _v[i%N];
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::operator-()
{
	Vector<N, T> result = Vector<N, T>().zero();
	for (int i = 0; i < N; i++) { result[i] = (-_v[i]); }
	return result;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::operator*=(const T s)
{
	for (int i = 0; i < N; i++) { _v[i] *= s; }
	return *this;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::operator/=(const T s)
{
	for (int i = 0; i < N; i++) { _v[i] /= s; }
	return *this;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::operator+=(const Vector<N, T>& v)
{
	for (int i = 0; i < N; i++) { _v[i] += v[i]; }
	return *this;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::operator-=(const Vector<N, T>& v)
{
	for (int i = 0; i < N; i++) { _v[i] -= v[i]; }
	return *this;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::operator*=(const Vector<N, T>& v)
{
	for (int i = 0; i < N; i++) { _v[i] *= v[i]; }
	return *this;
}

template <int N, class T>
Vector<N, T>& Vector<N, T>::operator/=(const Vector<N, T>& v)
{
	for (int i = 0; i < N; i++) { _v[i] /= v[i]; }
	return *this;
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::operator<(const T s) {
	Vector<N, T> result = Vector<N, T>().zero();
	for (int i = 0; i < N; i++) { result[i] = (_v[i] < s); }
	return result;
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::operator>(const T s) {
	Vector<N, T> result = Vector<N, T>().zero();
	for (int i = 0; i < N; i++) { result[i] = (_v[i] > s); }
	return result;
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::operator<(const Vector<N, T>& v) {
	Vector<N, T> result = Vector<N, T>().zero();
	for (int i = 0; i < N; i++) { result[i] = (_v[i] < v[i]); }
	return result;
}

template <int N, class T>
inline const Vector<N, T> Vector<N, T>::operator>(const Vector<N, T>& v) {
	Vector<N, T> result = Vector<N, T>().zero();
	for (int i = 0; i < N; i++) { result[i] = (_v[i] > v[i]); }
	return result;
}

template <int N, class T>
inline bool Vector<N, T>::operator==(const Vector<N, T>& v) {
	for (int i = 0; i < N; i++) { if (_v[i] != v[i]) { return false; } }
	return true;
}

template <int N, class T>
inline bool Vector<N, T>::operator!=(const Vector<N, T>& v) {
	return !(*this == v);
}

template <int N, class T>
inline Vector<N, T> transform::operator*(Vector<N, T> v, const T s)
{
	v *= s;
	return v;
}

template <int N, class T>
inline Vector<N, T> transform::operator/(Vector<N, T> v, const T s)
{
	v /= s;
	return v;
}

template <int N, class T>
inline Vector<N, T> transform::operator+(Vector<N, T> v1, const Vector<N, T>& v2)
{
	v1 += v2;
	return v1;
}

template <int N, class T>
inline Vector<N, T> transform::operator-(Vector<N, T> v1, const Vector<N, T>& v2)
{
	v1 -= v2;
	return v1;
}

template <int N, class T>
inline Vector<N, T> transform::operator*(Vector<N, T> v1, const Vector<N, T>& v2)
{
	v1 *= v2;
	return v1;
}

template <int N, class T>
inline Vector<N, T> transform::operator/(Vector<N, T> v1, const Vector<N, T>& v2)
{
	v1 /= v2;
	return v1;
}
