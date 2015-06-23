#include "stdafx.h"
#include "Color.h"

Namse::Color Namse::Color::operator+(const Namse::Color& _color) const
{
	return Namse::Color(m_R + _color.m_R
		, m_G + _color.m_G
		, m_B + _color.m_B);
}

Namse::Color Namse::Color::operator-() const
{
	return Namse::Color(-m_R, -m_G, -m_B);
}

Namse::Color Namse::Color::operator-(const Namse::Color& _color) const
{
	return *this + (-_color);
}

Namse::Color Namse::Color::operator*(float _factor) const
{
	return Namse::Color(m_R * _factor,
		m_G * _factor,
		m_B * _factor);
}

Namse::Color Namse::Color::operator/(float _factor) const
{
	return *this * (1.0 / _factor);
}

Namse::Color& Namse::Color::operator+=(const Namse::Color& _color)
{
	m_R += _color.m_R;
	m_G += _color.m_G;
	m_B += _color.m_B;
	return *this;
}

Namse::Color& Namse::Color::operator-=(const Namse::Color& _color)
{
	return *this += (-_color);
}

Namse::Color& Namse::Color::operator*=(float _factor)
{
	m_R *= _factor;
	m_G *= _factor;
	m_B *= _factor;
	return *this;
}

Namse::Color& Namse::Color::operator/=(float _factor)
{
	return *this *= (1.0 / _factor);
}
