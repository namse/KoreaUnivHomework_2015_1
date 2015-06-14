#include "stdafx.h"
#include "IntersectTest.h"

bool Namse::IntersectTest::IsIntersected(
	IN const Namse::Triangle* triangle, 
	IN const Namse::Vector& startPoint, 
	IN const Namse::Vector& rayVec, 
	IN const GLdouble maxDistance /*= MAX_DISTNACE*/, 
	OUT GLdouble* distance /*= nullptr*/, 
	OUT Namse::Vector* contactPoint /*= nullptr */)
{
	auto normal_Dot_Ray = triangle->m_NormalVector.DotProduct(rayVec);
	GLdouble retDistance = 0;
	if (normal_Dot_Ray < 0)
	{
		retDistance = (triangle->m_NormalVector.DotProduct(startPoint) - triangle->m_FirstVectorOnNormalVectorCoordination) / (-normal_Dot_Ray);

		if (retDistance >= 0.0f && retDistance < maxDistance)
		{
			auto retPoint = (rayVec) * retDistance + startPoint;


			if (distance)
				*distance = retDistance;
			if (contactPoint)
				*contactPoint = retPoint;
			
			return Namse::IntersectTest::IsInside(triangle, &retPoint);
		}
	}

	return false;
}

bool Namse::IntersectTest::IsInside(IN const Namse::Triangle* triangle, IN const Namse::Vector* point)
{
	for (int i = 0; i < 3; i++)
	{
		if (triangle->m_NormalVectors[i].DotProduct(*point) - triangle->m_Distnace[i] < 0) 
			return false;
	}
	return true;
}
