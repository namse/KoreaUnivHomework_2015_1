#pragma once
#include "Vector.h"
#include <vector>
namespace Namse
{
	class Vector;
	class Node
	{
	public:
		Node(){}

		virtual void MoveBy(Vector& vector);
		virtual void MoveTo(Vector& vector);

		//virtual void RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ) {}

		virtual	void	OnDraw(Vector& BasePosition);
		
		void			AddChild(
			Node*	node
			);

		void			RemoveChild(
			Node*	node
			);

		Vector m_Position;
	private:
		std::vector<Node*> m_Childs;
	};
}
