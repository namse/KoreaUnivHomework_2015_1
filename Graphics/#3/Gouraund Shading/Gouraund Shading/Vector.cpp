#include "stdafx.h"
#include "Vector.h"


Namse::Vector Namse::Vector::operator+ (const Namse::Vector& _vector) const
{
	return Vector(m_X + _vector.m_X, m_Y + _vector.m_Y, m_Z + _vector.m_Z);
}

Namse::Vector Namse::Vector::operator- () const
{
	return Vector(-m_X, -m_Y, -m_Z);
}

Namse::Vector Namse::Vector::operator- (const Namse::Vector& _vector) const
{
	return *this + (-_vector);
}

Namse::Vector Namse::Vector::operator* (GLdouble _factor) const
{
	return Vector(m_X * _factor, m_Y * _factor, m_Z * _factor);
}

Namse::Vector Namse::Vector::operator/ (GLdouble _factor) const
{
	return *this*(1.0 / _factor);
}

GLdouble Namse::Vector::DotProduct(const Namse::Vector& _vector) const
{
	return m_X * _vector.m_X + m_Y * _vector.m_Y + m_Z * _vector.m_Z;
}

Namse::Vector Namse::Vector::Unit() const
{
	return *this / Norm();
}

GLdouble Namse::Vector::Norm() const
{
	return pow(m_X*m_X + m_Y*m_Y + m_Z*m_Z, 0.5);
}

Namse::Vector Namse::Vector::CrossProduct(const Namse::Vector& _vector) const
{
	return Vector(m_Y * _vector.m_Z - m_Z * m_Y,
		m_Z * _vector.m_X - m_X * _vector.m_Z,
		m_X * _vector.m_Y - m_Y * _vector.m_X);
}

Namse::Vector& Namse::Vector::operator+=(const Namse::Vector& _vector)
{
	m_X += _vector.m_X;
	m_Y += _vector.m_Y;
	m_Z += _vector.m_Z;
	return *this;
}

Namse::Vector& Namse::Vector::operator-=(const Namse::Vector& _vector)
{
	return *this += (-_vector);
}

Namse::Vector& Namse::Vector::operator*=(GLdouble _factor)
{
	m_X *= _factor;
	m_Y *= _factor;
	m_Z *= _factor;
	return *this;
}

Namse::Vector& Namse::Vector::operator/=(GLdouble _factor)
{
	return *this *= (1.0 / _factor);
}

void Namse::Vector::MoveBy(Namse::Vector _vector)
{
	*this += _vector;
}

void Namse::Vector::RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ)
{
	// x axis
	m_X = 1.0			* m_X + 0 * m_Y + 0 * m_Z;
	m_Y = 0 * m_X + cos(_angleX)	* m_Y + -sin(_angleX)	* m_Z;
	m_Z = 0 * m_X + sin(_angleX)	* m_Y + cos(_angleX)	* m_Z;

	// y axis
	m_X = cos(_angleY)	* m_X + 0 * m_Y + sin(_angleY)	* m_Z;
	m_Y = 0 * m_X + 1 * m_Y + 0 * m_Z;
	m_Z = -sin(_angleY) * m_X + 0 * m_Y + cos(_angleX)	* m_Z;

	// y axis
	m_X = cos(_angleZ)	* m_X + -sin(_angleZ) * m_Y + 0 * m_Z;
	m_Y = sin(_angleZ)	* m_X + cos(_angleX)	* m_Y + 0 * m_Z;
	m_Z = 0 * m_X + 0 * m_Y + 1 * m_Z;
}

void Namse::Vector::Draw()
{
	glBegin(GL_POINTS);
	glColor3d(m_R, m_G, m_B);
	glVertex3d(m_X, m_Y, m_Z);
	glEnd();
}