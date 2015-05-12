#pragma once
struct Color
{
	GLdouble m_R, m_G, m_B;
	Color() : m_R(0), m_G(0), m_B(0)
	{}
	Color(GLdouble r, GLdouble g, GLdouble b)
		: m_R(r), m_G(g), m_B(b) {}
	Color operator+ (const Color& _color) const;
	Color operator- () const;
	Color operator- (const Color& _color) const;
	Color operator* (GLdouble _factor) const;
	Color operator/ (GLdouble _factor) const;
	Color& operator+= (const Color& _color);
	Color& operator-= (const Color& _color);
	Color& operator*= (GLdouble _factor);
	Color& operator/= (GLdouble _factor);
};

