#pragma once
#include "Node.h"
#include "Vector.h"
namespace Namse
{
	class Triangle :
		public Node
	{
	public:
		Vector m_Vector[3];

		Triangle(Vector& _first, Vector& _second, Vector& _third)
		{
			m_Vector[0] = _first, m_Vector[1] = _second, m_Vector[2] = _third;
		}
		Vector GetCenter();

		virtual void Draw();

		virtual void MoveBy(Vector _vector);
		virtual void RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ);
	};
}