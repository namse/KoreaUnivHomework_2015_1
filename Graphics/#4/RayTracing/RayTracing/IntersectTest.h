#pragma once
#include "Triangle.h"
#include "Vector.h"
#include "Line.h"
namespace Namse
{
	namespace IntersectTest
	{

		//				Triangles			//

		bool IsInside( 
			IN	const	Namse::Triangle*	triangle, 
			IN	const	Namse::Vector*		point
			);

		bool IsIntersected(
			IN	const	Namse::Triangle*	triangle,
			IN	const	Namse::Vector&		startPoint,
			IN	const	Namse::Vector&		rayVec,
			IN	const	GLdouble			maxDistance		=	MAX_DISTNACE,
			OUT			GLdouble*			distance		=	nullptr,
			OUT			Namse::Vector*		contactPoint	=	nullptr
			);

	};
}