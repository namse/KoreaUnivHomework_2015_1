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
		/*
		bool IsIntersected(
			IN	const	Namse::Triangle*	triangle,
			IN	const	Namse::Vector&		startPoint,
			IN	const	Namse::Vector&		rayVec,
			IN	const	GLdouble			maxDistance		=	MAX_DISTNACE,
			OUT			GLdouble*			distance		=	nullptr,
			OUT			Namse::Vector*		contactPoint	=	nullptr
			);*/

		// below code from http://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
		bool AABB_RAY_Test(Namse::Vector& origin, Namse::Vector& ray, Namse::Vector& B1, Namse::Vector& B2, float* p_length = nullptr);
		

		// below from https://en.wikipedia.org/wiki/M%C3%B6ller%E2%80%93Trumbore_intersection_algorithm
		bool IsIntersected(
			Triangle* triangle,
			Namse::Vector&    origin,  //Ray origin
			Namse::Vector&    ray,  //Ray direction
			OUT			GLdouble*			distance,
			OUT			Namse::Vector*		contactPoint);
	};
}