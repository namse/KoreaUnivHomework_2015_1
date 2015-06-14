#include "stdafx.h"
#include "GLMath.h"


// ----------------------------------------------------------------------------------------------------------------------------

mat4x4::mat4x4()
{
	M[0] = 1.0f; M[4] = 0.0f; M[8] = 0.0f; M[12] = 0.0f;
	M[1] = 0.0f; M[5] = 1.0f; M[9] = 0.0f; M[13] = 0.0f;
	M[2] = 0.0f; M[6] = 0.0f; M[10] = 1.0f; M[14] = 0.0f;
	M[3] = 0.0f; M[7] = 0.0f; M[11] = 0.0f; M[15] = 1.0f;
}

mat4x4::~mat4x4()
{
}

mat4x4::mat4x4(const mat4x4 &Matrix)
{
	for (int i = 0; i < 16; i++)
	{
		M[i] = Matrix.M[i];
	}
}

mat4x4::mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4)
{
	M[0] = col1.x; M[4] = col2.x; M[8] = col3.x; M[12] = col4.x;
	M[1] = col1.y; M[5] = col2.y; M[9] = col3.y; M[13] = col4.y;
	M[2] = col1.z; M[6] = col2.z; M[10] = col3.z; M[14] = col4.z;
	M[3] = col1.w; M[7] = col2.w; M[11] = col3.w; M[15] = col4.w;
}

mat4x4::mat4x4(float c1r1, float c1r2, float c1r3, float c1r4, float c2r1, float c2r2, float c2r3, float c2r4, float c3r1, float c3r2, float c3r3, float c3r4, float c4r1, float c4r2, float c4r3, float c4r4)
{
	M[0] = c1r1; M[4] = c2r1; M[8] = c3r1; M[12] = c4r1;
	M[1] = c1r2; M[5] = c2r2; M[9] = c3r2; M[13] = c4r2;
	M[2] = c1r3; M[6] = c2r3; M[10] = c3r3; M[14] = c4r3;
	M[3] = c1r4; M[7] = c2r4; M[11] = c3r4; M[15] = c4r4;
}

mat4x4& mat4x4::operator = (const mat4x4 &Matrix)
{
	for (int i = 0; i < 16; i++)
	{
		M[i] = Matrix.M[i];
	}

	return *this;
}

float& mat4x4::operator [] (int i)
{
	return M[i];
}

float* mat4x4::operator & ()
{
	return (float*)this;
}

mat4x4 operator * (const mat4x4 &Matrix1, const mat4x4 &Matrix2)
{
	mat4x4 Matrix3;

	Matrix3.M[0] = Matrix1.M[0] * Matrix2.M[0] + Matrix1.M[4] * Matrix2.M[1] + Matrix1.M[8] * Matrix2.M[2] + Matrix1.M[12] * Matrix2.M[3];
	Matrix3.M[1] = Matrix1.M[1] * Matrix2.M[0] + Matrix1.M[5] * Matrix2.M[1] + Matrix1.M[9] * Matrix2.M[2] + Matrix1.M[13] * Matrix2.M[3];
	Matrix3.M[2] = Matrix1.M[2] * Matrix2.M[0] + Matrix1.M[6] * Matrix2.M[1] + Matrix1.M[10] * Matrix2.M[2] + Matrix1.M[14] * Matrix2.M[3];
	Matrix3.M[3] = Matrix1.M[3] * Matrix2.M[0] + Matrix1.M[7] * Matrix2.M[1] + Matrix1.M[11] * Matrix2.M[2] + Matrix1.M[15] * Matrix2.M[3];
	Matrix3.M[4] = Matrix1.M[0] * Matrix2.M[4] + Matrix1.M[4] * Matrix2.M[5] + Matrix1.M[8] * Matrix2.M[6] + Matrix1.M[12] * Matrix2.M[7];
	Matrix3.M[5] = Matrix1.M[1] * Matrix2.M[4] + Matrix1.M[5] * Matrix2.M[5] + Matrix1.M[9] * Matrix2.M[6] + Matrix1.M[13] * Matrix2.M[7];
	Matrix3.M[6] = Matrix1.M[2] * Matrix2.M[4] + Matrix1.M[6] * Matrix2.M[5] + Matrix1.M[10] * Matrix2.M[6] + Matrix1.M[14] * Matrix2.M[7];
	Matrix3.M[7] = Matrix1.M[3] * Matrix2.M[4] + Matrix1.M[7] * Matrix2.M[5] + Matrix1.M[11] * Matrix2.M[6] + Matrix1.M[15] * Matrix2.M[7];
	Matrix3.M[8] = Matrix1.M[0] * Matrix2.M[8] + Matrix1.M[4] * Matrix2.M[9] + Matrix1.M[8] * Matrix2.M[10] + Matrix1.M[12] * Matrix2.M[11];
	Matrix3.M[9] = Matrix1.M[1] * Matrix2.M[8] + Matrix1.M[5] * Matrix2.M[9] + Matrix1.M[9] * Matrix2.M[10] + Matrix1.M[13] * Matrix2.M[11];
	Matrix3.M[10] = Matrix1.M[2] * Matrix2.M[8] + Matrix1.M[6] * Matrix2.M[9] + Matrix1.M[10] * Matrix2.M[10] + Matrix1.M[14] * Matrix2.M[11];
	Matrix3.M[11] = Matrix1.M[3] * Matrix2.M[8] + Matrix1.M[7] * Matrix2.M[9] + Matrix1.M[11] * Matrix2.M[10] + Matrix1.M[15] * Matrix2.M[11];
	Matrix3.M[12] = Matrix1.M[0] * Matrix2.M[12] + Matrix1.M[4] * Matrix2.M[13] + Matrix1.M[8] * Matrix2.M[14] + Matrix1.M[12] * Matrix2.M[15];
	Matrix3.M[13] = Matrix1.M[1] * Matrix2.M[12] + Matrix1.M[5] * Matrix2.M[13] + Matrix1.M[9] * Matrix2.M[14] + Matrix1.M[13] * Matrix2.M[15];
	Matrix3.M[14] = Matrix1.M[2] * Matrix2.M[12] + Matrix1.M[6] * Matrix2.M[13] + Matrix1.M[10] * Matrix2.M[14] + Matrix1.M[14] * Matrix2.M[15];
	Matrix3.M[15] = Matrix1.M[3] * Matrix2.M[12] + Matrix1.M[7] * Matrix2.M[13] + Matrix1.M[11] * Matrix2.M[14] + Matrix1.M[15] * Matrix2.M[15];

	return Matrix3;
}


vec4 operator * (const mat4x4 &Matrix, const vec4 &u)
{
	vec4 v;

	v.x = Matrix.M[0] * u.x + Matrix.M[4] * u.y + Matrix.M[8] * u.z + Matrix.M[12] * u.w;
	v.y = Matrix.M[1] * u.x + Matrix.M[5] * u.y + Matrix.M[9] * u.z + Matrix.M[13] * u.w;
	v.z = Matrix.M[2] * u.x + Matrix.M[6] * u.y + Matrix.M[10] * u.z + Matrix.M[14] * u.w;
	v.w = Matrix.M[3] * u.x + Matrix.M[7] * u.y + Matrix.M[11] * u.z + Matrix.M[15] * u.w;

	return v;
}


// ----------------------------------------------------------------------------------------------------------------------------

mat4x4 BiasMatrix = mat4x4(0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.5f, 0.0f, 0.5f, 0.5f, 0.5f, 1.0f);
mat4x4 BiasMatrixInverse = mat4x4(2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, 0.0f, 0.0f, 0.0f, 2.0f, 0.0f, -1.0f, -1.0f, -1.0f, 1.0f);

// ----------------------------------------------------------------------------------------------------------------------------
//
// 0 4  8 12 | + - + -
// 1 5  9 13 | - + - +
// 2 6 10 14 | + - + -
// 3 7 11 15 | - + - +
//
// ----------------------------------------------------------------------------------------------------------------------------

mat4x4 inverse(const mat4x4 &Matrix)
{
	const float *m = Matrix.M;

	float det = 0.0f;

	det += m[0] * det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15);
	det -= m[4] * det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15);
	det += m[8] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15);
	det -= m[12] * det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11);

	mat4x4 Inverse;

	Inverse.M[0] = det3x3sub(m, 5, 6, 7, 9, 10, 11, 13, 14, 15) / det;
	Inverse.M[1] = -det3x3sub(m, 1, 2, 3, 9, 10, 11, 13, 14, 15) / det;
	Inverse.M[2] = det3x3sub(m, 1, 2, 3, 5, 6, 7, 13, 14, 15) / det;
	Inverse.M[3] = -det3x3sub(m, 1, 2, 3, 5, 6, 7, 9, 10, 11) / det;
	Inverse.M[4] = -det3x3sub(m, 4, 6, 7, 8, 10, 11, 12, 14, 15) / det;
	Inverse.M[5] = det3x3sub(m, 0, 2, 3, 8, 10, 11, 12, 14, 15) / det;
	Inverse.M[6] = -det3x3sub(m, 0, 2, 3, 4, 6, 7, 12, 14, 15) / det;
	Inverse.M[7] = det3x3sub(m, 0, 2, 3, 4, 6, 7, 8, 10, 11) / det;
	Inverse.M[8] = det3x3sub(m, 4, 5, 7, 8, 9, 11, 12, 13, 15) / det;
	Inverse.M[9] = -det3x3sub(m, 0, 1, 3, 8, 9, 11, 12, 13, 15) / det;
	Inverse.M[10] = det3x3sub(m, 0, 1, 3, 4, 5, 7, 12, 13, 15) / det;
	Inverse.M[11] = -det3x3sub(m, 0, 1, 3, 4, 5, 7, 8, 9, 11) / det;
	Inverse.M[12] = -det3x3sub(m, 4, 5, 6, 8, 9, 10, 12, 13, 14) / det;
	Inverse.M[13] = det3x3sub(m, 0, 1, 2, 8, 9, 10, 12, 13, 14) / det;
	Inverse.M[14] = -det3x3sub(m, 0, 1, 2, 4, 5, 6, 12, 13, 14) / det;
	Inverse.M[15] = det3x3sub(m, 0, 1, 2, 4, 5, 6, 8, 9, 10) / det;

	return Inverse;
}

mat4x4 look(const Namse::Vector &eye, const Namse::Vector &center, const Namse::Vector &up)
{
	Namse::Vector Z = (eye - center).Unit();
	Namse::Vector X = up.CrossProduct(Z).Unit();
	Namse::Vector Y = Z.CrossProduct(X);

	mat4x4 View;

	View.M[0] = X.m_X;
	View.M[1] = Y.m_X;
	View.M[2] = Z.m_X;
	View.M[4] = X.m_Y;
	View.M[5] = Y.m_Y;
	View.M[6] = Z.m_Y;
	View.M[8] = X.m_Z;
	View.M[9] = Y.m_Z;
	View.M[10] = Z.m_Z;
	View.M[12] = -X.DotProduct(eye);
	View.M[13] = -Y.DotProduct(eye);
	View.M[14] = -Z.DotProduct(eye);

	return View;
}

mat4x4 ortho(float left, float right, float bottom, float top, float n, float f)
{
	mat4x4 Ortho;

	Ortho.M[0] = 2.0f / (right - left);
	Ortho.M[5] = 2.0f / (top - bottom);
	Ortho.M[10] = -2.0f / (f - n);
	Ortho.M[12] = -(right + left) / (right - left);
	Ortho.M[13] = -(top + bottom) / (top - bottom);
	Ortho.M[14] = -(f + n) / (f - n);

	return Ortho;
}

mat4x4 perspective(float fovy, float aspect, float n, float f)
{
	mat4x4 Perspective;

	float coty = 1.0f / tan(fovy * (float)M_PI / 360.0f);

	Perspective.M[0] = coty / aspect;
	Perspective.M[5] = coty;
	Perspective.M[10] = (n + f) / (n - f);
	Perspective.M[11] = -1.0f;
	Perspective.M[14] = 2.0f * n * f / (n - f);
	Perspective.M[15] = 0.0f;

	return Perspective;
}

mat4x4 rotate(float angle, const Namse::Vector &u)
{
	mat4x4 Rotate;

	angle = angle / 180.0f * (float)M_PI;

	Namse::Vector v = u.Unit();

	float c = 1.0f - cos(angle), s = sin(angle);

	Rotate.M[0] = 1.0f + c * (v.m_X * v.m_X - 1.0f);
	Rotate.M[1] = c * v.m_X * v.m_Y + v.m_Z * s;
	Rotate.M[2] = c * v.m_X * v.m_Z - v.m_Y * s;
	Rotate.M[4] = c * v.m_X * v.m_Y - v.m_Z * s;
	Rotate.M[5] = 1.0f + c * (v.m_Y * v.m_Y - 1.0f);
	Rotate.M[6] = c * v.m_Y * v.m_Z + v.m_X * s;
	Rotate.M[8] = c * v.m_X * v.m_Z + v.m_Y * s;
	Rotate.M[9] = c * v.m_Y * v.m_Z - v.m_X * s;
	Rotate.M[10] = 1.0f + c * (v.m_Z * v.m_Z - 1.0f);

	return Rotate;
}

mat4x4 scale(float x, float y, float z)
{
	mat4x4 Scale;

	Scale.M[0] = x;
	Scale.M[5] = y;
	Scale.M[10] = z;

	return Scale;
}

mat4x4 translate(float x, float y, float z)
{
	mat4x4 Translate;

	Translate.M[12] = x;
	Translate.M[13] = y;
	Translate.M[14] = z;

	return Translate;
}

mat4x4 transpose(const mat4x4 &Matrix)
{
	mat4x4 Transpose;

	Transpose.M[0] = Matrix.M[0];
	Transpose.M[1] = Matrix.M[4];
	Transpose.M[2] = Matrix.M[8];
	Transpose.M[3] = Matrix.M[12];
	Transpose.M[4] = Matrix.M[1];
	Transpose.M[5] = Matrix.M[5];
	Transpose.M[6] = Matrix.M[9];
	Transpose.M[7] = Matrix.M[13];
	Transpose.M[8] = Matrix.M[2];
	Transpose.M[9] = Matrix.M[6];
	Transpose.M[10] = Matrix.M[10];
	Transpose.M[11] = Matrix.M[14];
	Transpose.M[12] = Matrix.M[3];
	Transpose.M[13] = Matrix.M[7];
	Transpose.M[14] = Matrix.M[11];
	Transpose.M[15] = Matrix.M[15];

	return Transpose;
}




float det3x3sub(const float *m, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8)
{
	float det = 0.0f;

	det += m[i0] * det2x2sub(m, i4, i5, i7, i8);
	det -= m[i3] * det2x2sub(m, i1, i2, i7, i8);
	det += m[i6] * det2x2sub(m, i1, i2, i4, i5);

	return det;
}

float det2x2sub(const float *m, int i0, int i1, int i2, int i3)
{
	return m[i0] * m[i3] - m[i2] * m[i1];
}




Namse::Vector rotate(const Namse::Vector &u, float angle, const Namse::Vector &v)
{
	auto& retVec4 = rotate(angle, v) * vec4(u, 1.0f);
	Namse::Vector ret;
	ret.m_X = retVec4.x;
	ret.m_Y = retVec4.y;
	ret.m_Z = retVec4.z;
	return ret;
}
