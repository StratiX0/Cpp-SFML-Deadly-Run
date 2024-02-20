#pragma once

#include <cmath>

#pragma warning(push)
#pragma warning(disable : 4244)

namespace Maths
{

template<typename T>
Vector2<T>::Vector2() : x(0), y(0) {}

template<typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2& rhs)
{
	return Vector2(x + rhs.x, y + rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2& rhs)
{
	return Vector2(x - rhs.x, y - rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2& rhs)
{
	return Vector2(x * rhs.x, y * rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2& rhs)
{
	return Vector2(x / rhs.x, y / rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const T& rhs)
{
	return Vector2(x * rhs, y * rhs);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const T& rhs)
{
	return Vector2(x / rhs, y / rhs);
}

template<typename T>
Vector2<T> Vector2<T>::operator+=(const Vector2& rhs)
{
	x += rhs.x;
	y += rhs.y;
	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator-=(const Vector2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*=(const Vector2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator/=(const Vector2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator*=(const T& rhs)
{
	x *= rhs;
	y *= rhs;
	return *this;
}

template<typename T>
Vector2<T> Vector2<T>::operator/=(const T& rhs)
{
	x /= rhs;
	y /= rhs;
	return *this;
}

template<typename T>
float Vector2<T>::Dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

template<typename T>
float Vector2<T>::Cross(const Vector2& rhs) const
{
	return x * rhs.y - y * rhs.x;
}

template<typename T>
float Vector2<T>::Magnitude() const
{
	return sqrt(x * x + y * y);
}

template<typename T>
float Vector2<T>::MagnitudeSquared() const
{
	return x * x + y * y;
}

template<typename T>
Vector2<T> Vector2<T>::Normalize() const
{
	return Vector2(x / Magnitude(), y / Magnitude());
}

template<typename T>
float Vector2<T>::Distance(const Vector2<T>& rhs) const
{
	return std::sqrt((x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y));
}

template<typename T>
float Vector2<T>::DistanceSquared(const Vector2& rhs) const
{
	return (x - rhs.x) * (x - rhs.x) + (y - rhs.y) * (y - rhs.y);
}

template<typename T>
float Vector2<T>::Angle(const Vector2& rhs) const
{
	return std::acos(this->Dot(rhs) / (Magnitude() * rhs.Magnitude()));
}

template<typename T>
Vector2<T> Vector2<T>::Rotate(const T& angle) const
{
	return Vector2(x * std::cos(angle) - y * std::sin(angle), x * std::sin(angle) + y * std::cos(angle));
}

template<typename T>
Vector2<T> Vector2<T>::Lerp(const Vector2& lhs, const Vector2<T>& rhs, const T& alpha)
{
	return Vector2(lhs.x * (1 - alpha) + rhs.x * alpha, lhs.y * (1 - alpha) + rhs.y * alpha);
}

template<typename T>
Vector2<T> Vector2<T>::Max(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x > rhs.x ? lhs.x : rhs.x, lhs.y > rhs.y ? lhs.y : rhs.y);
}

template<typename T>
Vector2<T> Vector2<T>::Min(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x < rhs.x ? lhs.x : rhs.x, lhs.y < rhs.y ? lhs.y : rhs.y);
}

template<typename T>
T Vector2<T>::GetX()
{
	return x;
}

template<typename T>
T Vector2<T>::GetY()
{
	return y;
}

template<typename T>
void Vector2<T>::SetX(const T& new_x)
{
	x = new_x;
}

template<typename T>
void Vector2<T>::SetY(const T& new_y)
{
	y = new_y;
}

template<typename T>
void Vector2<T>::SetXY(const T& new_x, const T& new_y)
{
	x = new_x;
	y = new_y;
}

template<typename T>
void Vector2<T>::SetXY(const Vector2& rhs)
{
	x = rhs.x;
	y = rhs.y;
}

template<typename T>
const Vector2<T> Vector2<T>::Zero(0, 0);

template<typename T>
const Vector2<T> Vector2<T>::One(1, 1);

template<typename T>
const Vector2<T> Vector2<T>::UnitX(1, 0);

template<typename T>
const Vector2<T> Vector2<T>::UnitY(0, 1);

template<typename T>
const Vector2<T> Vector2<T>::Up(0, -1);

template<typename T>
const Vector2<T> Vector2<T>::Down(0, 1);

template<typename T>
const Vector2<T> Vector2<T>::Left(-1, 0);

template<typename T>
const Vector2<T> Vector2<T>::Right(1, 0);


}

#pragma warning(pop)