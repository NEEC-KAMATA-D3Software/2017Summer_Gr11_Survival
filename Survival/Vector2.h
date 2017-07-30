#pragma once
#ifndef _VECTOR2_H_
#define _VECTOR2_H_

template<class T>
struct Vector2{
public:
	Vector2() :X(0), Y(0) {};
	Vector2(T _x, T _y) :X(_x), Y(_y) {}

	~Vector2() {}

	//計算
	Vector2 operator /(const Vector2& other) {
		return Vector2(X / other.X, Y / other.Y);
	}
	Vector2 operator /(const float& _f) const{
		return Vector2(X / _f, Y / _f);
	}
	Vector2 operator *(const float& _f) const{
		return Vector2(X * _f, Y * _f);
	}
	Vector2 operator *(const Vector2& other) {
		return Vector2(X * other.X, Y * other.Y);
	}
	Vector2 operator +(const Vector2& other) const{
		return Vector2(X + other.X, Y + other.Y);
	}
	Vector2 operator -(const Vector2& other) const {
		return Vector2(X - other.X, Y - other.Y);
	}

	//代入
	Vector2& operator =(const Vector2& other) {
		X = other.X;
		Y = other.Y;
		return *this;
	}
	Vector2& operator +=(const Vector2& other) {
		X += other.X;
		Y += other.Y;
		return *this;
	}
	Vector2& operator -=(const Vector2& other) {
		X -= other.X;
		Y -= other.Y;
		return *this;
	}
	Vector2& operator *=(const Vector2& other) {
		X *= other.X;
		Y *= other.Y;
		return *this;
	}
	Vector2& operator /=(const Vector2& other) {
		X /= other.X;
		Y /= other.Y;
		return *this;
	}

	bool operator ==(const Vector2& other) {
		bool sameX = (int)X == (int)other.X;
		bool sameY = (int)Y == (int)other.Y;
		return sameX && sameY;
	}


	//静的
	static Vector2 Zero()	{ return Vector2( 0.0f,  0.0f); }
	static Vector2 One()	{ return Vector2( 1.0f,  1.0f); }
	static Vector2 Up()		{ return Vector2( 0.0f, -1.0f); }
	static Vector2 Down()	{ return Vector2( 0.0f,  1.0f); }
	static Vector2 Left()	{ return Vector2(-1.0f,  0.0f); }
	static Vector2 Right()	{ return Vector2( 1.0f,  0.0f); }

	//計算（その他）
	static float Length(Vector2 v) {
		return sqrt(v.X * v.X + v.Y * v.Y);
	}

	T X;
	T Y;
};

using Point2 = Vector2<int>;
using Float2 = Vector2<float>;

#endif // !_VECTOR2_H_
