#include "stdafx.h"
#include "Color.h"

Color Color::operator+(const Color& _color) const
{
	return Color(m_R + _color.m_R
		, m_G + _color.m_G
		, m_B + _color.m_B);
}

Color Color::operator-() const
{
	return Color(-m_R, -m_G, -m_B);
}

Color Color::operator-(const Color& _color) const
{
	return *this + (-_color);
}

Color Color::operator*(GLdouble _factor) const
{
	return Color(m_R * _factor,
		m_G * _factor,
		m_B * _factor);
}

Color Color::operator/(GLdouble _factor) const
{
	return *this * (1.0 / _factor);
}

Color& Color::operator+=(const Color& _color)
{
	m_R += _color.m_R;
	m_G += _color.m_G;
	m_B += _color.m_B;
	return *this;
}

Color& Color::operator-=(const Color& _color)
{
	return *this += (-_color);
}

Color& Color::operator*=(GLdouble _factor)
{
	m_R *= _factor;
	m_G *= _factor;
	m_B *= _factor;
	return *this;
}

Color& Color::operator/=(GLdouble _factor)
{
	return *this *= (1.0 / _factor);
}
