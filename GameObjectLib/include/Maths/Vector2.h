#pragma once

namespace Maths
{
	template<typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2();
		//Constructor
		Vector2(T x, T y);
		//Destructor
		~Vector2() = default;

		Vector2(const Vector2& _other) = default;
		Vector2(Vector2&& _other) noexcept = default;
		Vector2& operator=(const Vector2& _other) = default;
		Vector2& operator=(Vector2&& _other) noexcept = default;

		//Addition
		Vector2 operator+(const Vector2& rhs);
		//Subtraction
		Vector2 operator-(const Vector2& rhs);
		//Multiplication
		Vector2 operator*(const Vector2& rhs);
		//Division
		Vector2 operator/(const Vector2& rhs);

		//Multiplication
		Vector2 operator*(const T& rhs);
		//Division
		Vector2 operator/(const T& rhs);

		//Addition
		Vector2 operator+=(const Vector2& rhs);
		//Subtraction
		Vector2 operator-=(const Vector2& rhs);
		//Multiplication
		Vector2 operator*=(const Vector2& rhs);
		//Division
		Vector2 operator/=(const Vector2& rhs);

		//Multiplication
		Vector2 operator*=(const T& rhs);
		//Division
		Vector2 operator/=(const T& rhs);

		//Dot Product
		float Dot(const Vector2& rhs) const;
		//Cross Product
		float Cross(const Vector2& rhs) const;
		//Magnitude
		float Magnitude() const;
		//Magnitude Squared
		float MagnitudeSquared() const;
		//Normalize
		Vector2 Normalize() const;
		//Distance
		float Distance(const Vector2& rhs) const;
		//Distance Squared
		float DistanceSquared(const Vector2& rhs) const;
		//Angle
		float Angle(const Vector2& rhs) const;
		//Rotate
		Vector2 Rotate(const T& angle) const;

		//Lerp
		static Vector2 Lerp(const Vector2& lhs, const Vector2& rhs, const T& alpha);
		//Max
		static Vector2 Max(const Vector2& lhs, const Vector2& rhs);
		//Min
		static Vector2 Min(const Vector2& lhs, const Vector2& rhs);

		//Get the X value
		T GetX();
		//Get the Y value
		T GetY();
		//Set the X value
		void SetX(const T& new_x);
		//Set the Y value
		void SetY(const T& new_y);
		//Set the X and Y values
		void SetXY(const T& new_x, const T& new_y);
		//Set the X and Y values
		void SetXY(const Vector2& rhs);
		//Set the X and Y values

		static const Vector2 Zero;
		static const Vector2 One;
		static const Vector2 UnitX;
		static const Vector2 UnitY;
		static const Vector2 Up;
		static const Vector2 Down;
		static const Vector2 Left;
		static const Vector2 Right;

		friend bool operator==(const Vector2& _lhs, const Vector2& _rhs)
		{
			return _lhs.x == _rhs.x && _lhs.y == _rhs.y;
		}

		friend bool operator!=(const Vector2& _lhs, const Vector2& _rhs) { return !(_lhs == _rhs); }
	};

	using Vector2i = Vector2<int>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2f = Vector2<float>;
	using Vector2d = Vector2<double>;
}

template class Maths::Vector2<int>;
template class Maths::Vector2<unsigned int>;
template class Maths::Vector2<float>;
template class Maths::Vector2<double>;

#include "Maths/Vector2.inl"
