#pragma once
#include "Node.h"
#include "Vector.h"
namespace Namse
{
	class Triangle :
		public Node
	{
	public:
		Vector* m_Vector[3];

		Triangle(Vector* _first, Vector* _second, Vector* _third)
			:m_ReflectionFactor(0.5), m_TransmissionFactor(0.3)
		{
			m_Vector[0] = _first, m_Vector[1] = _second, m_Vector[2] = _third;
		}
		Vector GetCenter();

		virtual	void	MoveBy(Vector _vector);
		virtual	void	RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ);

		virtual	void	OnDraw(Vector& BasePosition);

		void	GetColor(Namse::Vector inPoint, Namse::Color& color);

		Vector m_AbsolutePosition;

		// for octree
		Vector m_MinVector;
		Vector m_MaxVector;

		Vector m_NormalVector;
		GLdouble m_FirstVectorOnNormalVectorCoordination;

		Vector m_NormalVectors[3];
		GLdouble m_Distnace[3];

		GLdouble m_ReflectionFactor;
		GLdouble m_TransmissionFactor;
	};
}