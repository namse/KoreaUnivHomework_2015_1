#pragma once
#include "Node.h"
#include "Vector.h"
namespace Namse
{
	class Line :
		public Node
	{
	public:
		Vector m_From;
		Vector m_To;
		Line(Vector& from, Vector& to)
			:m_From(from), m_To(to) {}
		virtual void Draw();
	};
}