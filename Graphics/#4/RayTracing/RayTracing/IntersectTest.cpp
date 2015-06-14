#include "stdafx.h"
#include "IntersectTest.h"
/*
bool Namse::IntersectTest::IsIntersected(
	IN const Namse::Triangle* triangle, 
	IN const Namse::Vector& startPoint, 
	IN const Namse::Vector& rayVec, 
	IN const GLdouble maxDistance
	OUT GLdouble* distance
	OUT Namse::Vector* contactPoint)
{
	auto normal_Dot_Ray = triangle->m_NormalVector.DotProduct(rayVec);
	GLdouble retDistance = 0;
	//if (normal_Dot_Ray > 0) normal_Dot_Ray *= -1;
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
*/
#define EPSILON 0.000001

bool Namse::IntersectTest::IsIntersected(
	Namse::Triangle* triangle,
	Namse::Vector&    origin,  //Ray origin
	Namse::Vector&    ray,  //Ray direction
	OUT			GLdouble*			distance,
	OUT			Namse::Vector*		contactPoint)
{
	Namse::Vector e1, e2;  //Edge1, Edge2
	Namse::Vector P, Q, T;
	float det, inv_det, u, v;
	float t;
	Namse::Vector AbsVector[3]{Namse::Vector(*triangle->m_Vector[0] + triangle->m_AbsolutePosition),
		Namse::Vector(*triangle->m_Vector[1] + triangle->m_AbsolutePosition),
		Namse::Vector(*triangle->m_Vector[2] + triangle->m_AbsolutePosition)};

	//Find vectors for two edges sharing triangle->m_Vector[0]
	e1 = AbsVector[1] - AbsVector[0];
	e2 = AbsVector[2] - AbsVector[0];
	//Begin calculating determinant - also used to calculate u parameter
	P = ray.CrossProduct(e2);
	//if determinant is near zero, ray lies in plane of triangle
	det = e1.DotProduct(P);

	//NOT CULLING
	if (det > -EPSILON && det < EPSILON) return false;
	inv_det = 1.f / det;

	//calculate distance from triangle->m_Vector[0] to ray origin
	T = origin - AbsVector[0];

	//Calculate u parameter and test bound
	u = T.DotProduct(P) * inv_det;

	//The intersection lies outside of the triangle
	if (u < 0.f || u > 1.f) return false;

	//Prepare to test v parameter
	Q = T.CrossProduct(e1);

	//Calculate V parameter and test bound
	v = ray.DotProduct(Q) * inv_det;
	//The intersection lies outside of the triangle
	if (v < 0.f || u + v  > 1.f) return false;

	t = e2.DotProduct(Q) * inv_det;

	if (t > EPSILON) { //ray intersection
		*contactPoint = origin + ray * t;
		*distance = (origin - *contactPoint).Norm();
		return true;
	}

	// No hit, no win
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
bool Namse::IntersectTest::AABB_RAY_Test(Namse::Vector& origin, Namse::Vector& ray, Namse::Vector& B1, Namse::Vector& B2, float* p_length /* = nullptr */)
{
	Namse::Vector dirfrac;

	// ray is unit direction vector of ray
	dirfrac.m_X = 1.0f / ray.m_X;
	dirfrac.m_Y = 1.0f / ray.m_Y;
	dirfrac.m_Z = 1.0f / ray.m_Z;

	// B1 is the corner of AABB with minimal coordinates - left bottom, B2 is maximal corner
	// origin is origin of ray
	float t1 = (B1.m_X - origin.m_X)*dirfrac.m_X;
	float t2 = (B2.m_X - origin.m_X)*dirfrac.m_X;
	float t3 = (B1.m_Y - origin.m_Y)*dirfrac.m_Y;
	float t4 = (B2.m_Y - origin.m_Y)*dirfrac.m_Y;
	float t5 = (B1.m_Z - origin.m_Z)*dirfrac.m_Z;
	float t6 = (B2.m_Z - origin.m_Z)*dirfrac.m_Z;

	float tmin = std::max(std::max(std::min(t1, t2), std::min(t3, t4)), std::min(t5, t6));
	float tmax = std::min(std::min(std::max(t1, t2), std::max(t3, t4)), std::max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behing us
	if (tmax < 0)
	{
		if (p_length != nullptr)
			*p_length = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		if (p_length != nullptr)
			*p_length = tmax;
		return false;
	}

	if (p_length != nullptr)
		*p_length = tmin;
	return true;
}
