#pragma once
#include "Vector.h"
// code base from glMath. 

class vec4
{
public:
	union{
		struct{ float x, y, z, w; };
		struct{ float s, t, p, q; };
		struct{ float r, g, b, a; };
	};
	vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f){}
	~vec4(){}
	vec4(float num) : x(num), y(num), z(num), w(num){}
	vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){}
	vec4(const Namse::Vector &u, float w) : x(u.m_X), y(u.m_Y), z(u.m_Z), w(w){}
	vec4(const vec4 &u) : x(u.x), y(u.y), z(u.z), w(u.w){}
	vec4& operator = (const vec4 &u){ x = u.x; y = u.y; z = u.z; w = u.w; return *this; }
	vec4 operator - (){ return vec4(-x, -y, -z, -w); }
	float* operator & (){ return (float*)this; }
	vec4& operator += (float num){ x += num; y += num; z += num; w += num; return *this; }
	vec4& operator += (const vec4 &u){ x += u.x; y += u.y; z += u.z; w += u.w; return *this; }
	vec4& operator -= (float num){ x -= num; y -= num; z -= num; w -= num; return *this; }
	vec4& operator -= (const vec4 &u){ x -= u.x; y -= u.y; z -= u.z; w -= u.w; return *this; }
	vec4& operator *= (float num){ x *= num; y *= num; z *= num; w *= num; return *this; }
	vec4& operator *= (const vec4 &u){ x *= u.x; y *= u.y; z *= u.z; w *= u.w; return *this; }
	vec4& operator /= (float num){ x /= num; y /= num; z /= num; w /= num; return *this; }
	vec4& operator /= (const vec4 &u){ x /= u.x; y /= u.y; z /= u.z; w /= u.w; return *this; }
	friend vec4 operator + (const vec4 &u, float num){ return vec4(u.x + num, u.y + num, u.z + num, u.w + num); }
	friend vec4 operator + (float num, const vec4 &u){ return vec4(num + u.x, num + u.y, num + u.z, num + u.w); }
	friend vec4 operator + (const vec4 &u, const vec4 &v){ return vec4(u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w); }
	friend vec4 operator - (const vec4 &u, float num){ return vec4(u.x - num, u.y - num, u.z - num, u.w - num); }
	friend vec4 operator - (float num, const vec4 &u){ return vec4(num - u.x, num - u.y, num - u.z, num - u.w); }
	friend vec4 operator - (const vec4 &u, const vec4 &v){ return vec4(u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w); }
	friend vec4 operator * (const vec4 &u, float num){ return vec4(u.x * num, u.y * num, u.z * num, u.w * num); }
	friend vec4 operator * (float num, const vec4 &u){ return vec4(num * u.x, num * u.y, num * u.z, num * u.w); }
	friend vec4 operator * (const vec4 &u, const vec4 &v){ return vec4(u.x * v.x, u.y * v.y, u.z * v.z, u.w * v.w); }
	friend vec4 operator / (const vec4 &u, float num){ return vec4(u.x / num, u.y / num, u.z / num, u.w / num); }
	friend vec4 operator / (float num, const vec4 &u){ return vec4(num / u.x, num / u.y, num / u.z, num / u.w); }
	friend vec4 operator / (const vec4 &u, const vec4 &v){ return vec4(u.x / v.x, u.y / v.y, u.z / v.z, u.w / v.w); }
};

class mat4x4
{
public:
	float M[16];
	mat4x4();
	~mat4x4();
	mat4x4(const mat4x4 &Matrix);
	mat4x4(const vec4 &col1, const vec4 &col2, const vec4 &col3, const vec4 &col4);
	mat4x4(float c1r1, float c1r2, float c1r3, float c1r4, float c2r1, float c2r2, float c2r3, float c2r4, float c3r1, float c3r2, float c3r3, float c3r4, float c4r1, float c4r2, float c4r3, float c4r4);
	mat4x4& operator = (const mat4x4 &Matrix);
	float& operator [] (int i);
	float* operator & ();
	friend mat4x4 operator * (const mat4x4 &Matrix1, const mat4x4 &Matrix2);
	friend vec4 operator * (const mat4x4 &Matrix, const vec4 &u);
};

mat4x4 rotate(float angle, const Namse::Vector &u);
Namse::Vector rotate(const Namse::Vector &u, float angle, const Namse::Vector &v);


float det3x3sub(const float *m, int i0, int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8);
float det2x2sub(const float *m, int i0, int i1, int i2, int i3);

extern mat4x4 BiasMatrix;
extern mat4x4 BiasMatrixInverse;