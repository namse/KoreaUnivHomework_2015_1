#pragma once
namespace Namse
{
	class Vector;
	class Node
	{
	public:
		Node() : m_R(0), m_G(0), m_B(0) {}
		virtual void Draw() {}

		virtual void MoveBy(Vector& vector) {}

		virtual void RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ) {}

		void SetColor(GLdouble r, GLdouble g, GLdouble b){ m_R = r, m_G = g, m_B = b; }

		GLdouble m_R;
		GLdouble m_G;
		GLdouble m_B;
	};
}
