#pragma once
#ifndef _MATRIX2_H_
#define _MATRIX2_H_

#include "Vector2.h"
#include <math.h>

#define PI 3.1415926

struct Matrix2 {
	Matrix2() : M{ {0,0}, {0,0} } {}
	Matrix2(float m1, float m2, float m3, float m4) {
		M[0][0] = m1;	M[0][1] = m2;
		M[1][0] = m3;	M[1][1] = m4;
	}

	~Matrix2() {}


	static Float2 Rotate(const Float2& v, float radius) {
		float _sin = sin(radius);
		float _cos = cos(radius);
		return Float2(v.X * _cos - v.Y * _sin, v.X * _sin + v.Y * _cos);
	}


	

	float M[2][2];
};

#endif // !_MATRIX_H_


