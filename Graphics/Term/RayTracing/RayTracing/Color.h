#pragma once
namespace Namse
{
	struct Color
	{
		float m_R, m_G, m_B;
		Color() : m_R(0), m_G(0), m_B(0)
		{}
		Color(float r, float g, float b)
			: m_R(r), m_G(g), m_B(b) {}
		Color operator+ (const Color& _color) const;
		Color operator- () const;
		Color operator- (const Color& _color) const;
		Color operator* (float _factor) const;
		Color operator/ (float _factor) const;
		Color& operator+= (const Color& _color);
		Color& operator-= (const Color& _color);
		Color& operator*= (float _factor);
		Color& operator/= (float _factor);
	};
}

