#include "stdafx.h"
#include "Octree.h"
#include <limits>
#include "IntersectTest.h"



Namse::Octree::Octree()
{
	m_Depth = 0;
	memset(m_Next, NULL, sizeof(m_Next));
	m_Triangles.reserve(1024);
}

Namse::Octree::Octree(Namse::Vector& center, float width, unsigned int depth)
	:m_Center(center), m_Width(width), m_Depth(depth)
	, m_MinX(center.m_X - m_Width / 2), m_MaxX(center.m_X + m_Width / 2)
	, m_MinY(center.m_Y - m_Width / 2), m_MaxY(center.m_Y + m_Width / 2)
	, m_MinZ(center.m_Z - m_Width / 2), m_MaxZ(center.m_Z + m_Width / 2)
{
	memset(m_Next, NULL, sizeof(m_Next));
	m_Triangles.reserve(1024);
}


Namse::Octree::~Octree()
{
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 2; z++)
				if (m_Next[x][y][z] != nullptr)
					delete m_Next[x][y][z];
}

void Namse::Octree::Clear()
{
	m_Triangles.clear();
	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 2; z++)
				if (m_Next[x][y][z] != nullptr)
					m_Next[x][y][z]->Clear();
}

void Namse::Octree::Add(Triangle* triangle)
{
	// bigger than AABB

	if (MAX_OCTREE_TREE == m_Depth
		||
		((triangle->m_MinVector.m_X <= m_MinX)
		&& (triangle->m_MaxVector.m_X > m_MaxX)
		&& (triangle->m_MinVector.m_Y <= m_MinY)
		&& (triangle->m_MaxVector.m_Y > m_MaxY)
		&& (triangle->m_MinVector.m_Z <= m_MinZ)
		&& (triangle->m_MaxVector.m_Z > m_MaxZ)))
	{
		m_Triangles.push_back(triangle);
	}
	else if (MAX_OCTREE_TREE > m_Depth)
	{
		int xInit, xMax, yInit, yMax, zInit, zMax;
		xInit = yInit = zInit = 0;
		xMax = yMax = zMax = 2;
		if (triangle->m_MinVector.m_X > m_Center.m_X)
			xInit = 1;
		if (triangle->m_MinVector.m_Y > m_Center.m_Y)
			yInit = 1;
		if (triangle->m_MinVector.m_Z > m_Center.m_Z)
			zInit = 1;
		if (triangle->m_MaxVector.m_X <= m_Center.m_X)
			xMax = 1;
		if (triangle->m_MaxVector.m_Y <= m_Center.m_Y)
			yMax = 1;
		if (triangle->m_MaxVector.m_Z <= m_Center.m_Z)
			zMax = 1;

		for (int x = xInit; x < xMax; x++)
			for (int y = yInit; y < yMax; y++)
				for (int z = zInit; z < zMax; z++)
				{
					if (m_Next[x][y][z] == nullptr)
						m_Next[x][y][z] = new Octree(
						m_Center + Namse::Vector(
						(m_Width * (2 * x - 1) / 4),
						(m_Width * (2 * y - 1) / 4),
						(m_Width * (2 * z - 1) / 4))
						, m_Width / 2, m_Depth + 1);

					m_Next[x][y][z]->Add(triangle);
				}
	}
}

void Namse::Octree::Reset(Namse::Vector& center, float width)
{
	m_Center = center;
	m_Width = width;

	m_MinX = center.m_X - m_Width / 2.f; m_MaxX = center.m_X + m_Width / 2.f;
	m_MinY = center.m_Y - m_Width / 2.f; m_MaxY = center.m_Y + m_Width / 2.f;
	m_MinZ = center.m_Z - m_Width / 2.f; m_MaxZ = center.m_Z + m_Width / 2.f;

	m_Triangles.clear();

	for (int x = 0; x < 2; x++)
		for (int y = 0; y < 2; y++)
			for (int z = 0; z < 2; z++)
				if (m_Next[x][y][z] != nullptr)
					m_Next[x][y][z]->Reset(m_Center + Namse::Vector(
					(m_Width * (2 * x - 1) / 4),
					(m_Width * (2 * y - 1) / 4),
					(m_Width * (2 * z - 1) / 4))
					, width / 2);
}

bool Namse::Octree::FindNearestTriangle(IN Vector& startPoint, IN Vector& rayVec, IN GLdouble maxDistance, OUT GLdouble& distance, OUT Namse::Vector& contactVector, OUT Triangle** triangle)
{
	// OUT
	Triangle* retTri = nullptr;
	GLdouble currentShortestDistance = maxDistance;
	Namse::Vector retContactVector;

	for (auto& tri :m_Triangles)
	{
		GLdouble distance;
		Namse::Vector contactPoint;
		if (Namse::IntersectTest::IsIntersected(tri, startPoint, rayVec, currentShortestDistance,
			&distance, &contactPoint))
		{
			if (distance < currentShortestDistance && distance > 0)
			{
				retTri = tri;
				currentShortestDistance = distance;
				retContactVector = contactPoint;
			}
		}
	}

	// TODO
	// Optimize - 현재까지 발견된 가장 가까운 삼각형 vs 현재 Octree Node의 위치


	if (m_Depth < MAX_OCTREE_TREE)
	{
		// x = centerX
		if (rayVec.m_X != 0)
		{
			GLdouble a = (m_Center.m_X - startPoint.m_X) / rayVec.m_X;
			if (a >= 0)
			{
				GLdouble x_Y = startPoint.m_Y + rayVec.m_Y * a;
				GLdouble x_Z = startPoint.m_Z + rayVec.m_Z * a;

				int x, y, z;
				if (x_Y > m_MinY && x_Y <= m_MaxY
					&& x_Z > m_MinZ && x_Z <= m_MaxZ)
				{
					if (x_Y <= m_Center.m_Y)
						y = 0;
					else
						y = 1;
					if (x_Z <= m_Center.m_Z)
						z = 0;
					else
						z = 1;

					for (x = 0; x < 2; x++)
					{
						GLdouble distance;
						Namse::Vector contactPoint;
						Namse::Triangle* tri;
						if (m_Next[x][y][z] != nullptr
							&& m_Next[x][y][z]->FindNearestTriangle(startPoint, rayVec, currentShortestDistance
							, distance, contactPoint, &tri))
						{
							if (distance < currentShortestDistance)
							{
								retTri = tri;
								currentShortestDistance = distance;
								retContactVector = contactPoint;
							}
						}
					}
				}
			}
		}


		// y = centerY

		// x = centerX
		if (rayVec.m_Y != 0)
		{
			GLdouble b = (m_Center.m_Y - startPoint.m_Y) / rayVec.m_Y;
			if (b >= 0)
			{
				GLdouble y_Z = startPoint.m_Z + rayVec.m_Z * b;
				GLdouble y_X = startPoint.m_X + rayVec.m_X * b;

				int x, y, z;
				if (y_Z > m_MinZ && y_Z <= m_MaxZ
					&& y_X > m_MinX && y_X <= m_MaxX)
				{
					if (y_Z <= m_Center.m_Z)
						z = 0;
					else
						z = 1;
					if (y_X <= m_Center.m_X)
						x = 0;
					else
						x = 1;

					for (y = 0; y < 2; y++)
					{
						GLdouble distance;
						Namse::Vector contactPoint;
						Namse::Triangle* tri;
						if (m_Next[x][y][z] != nullptr
							&& m_Next[x][y][z]->FindNearestTriangle(startPoint, rayVec, currentShortestDistance
							, distance, contactPoint, &tri))
						{
							if (distance < currentShortestDistance)
							{
								retTri = tri;
								currentShortestDistance = distance;
								retContactVector = contactPoint;
							}
						}
					}
				}
			}
		}


		// z = centerZ
		if (rayVec.m_Z != 0)
		{
			GLdouble c = (m_Center.m_Z - startPoint.m_Z) / rayVec.m_Z;
			if (c >= 0)
			{
				GLdouble z_X = startPoint.m_X + rayVec.m_X * c;
				GLdouble z_Y = startPoint.m_Y + rayVec.m_Y * c;

				int x, y, z;
				if (z_Y > m_MinY && z_Y <= m_MaxY
					&& z_X > m_MinX && z_X <= m_MaxX)
				{
					if (z_Y <= m_Center.m_Y)
						y = 0;
					else
						y = 1;
					if (z_X <= m_Center.m_X)
						x = 0;
					else
						x = 1;

					for (z = 0; z < 2; z++)
					{
						GLdouble distance;
						Namse::Vector contactPoint;
						Namse::Triangle* tri;
						if (m_Next[x][y][z] != nullptr
							&& m_Next[x][y][z]->FindNearestTriangle(startPoint, rayVec, currentShortestDistance
							, distance, contactPoint, &tri))
						{
							if (distance < currentShortestDistance)
							{
								retTri = tri;
								currentShortestDistance = distance;
								retContactVector = contactPoint;
							}
						}
					}
				}
			}
		}
	}
	
	distance = currentShortestDistance;
	contactVector = retContactVector;
	*triangle = retTri;
	if (*triangle != nullptr)
		return true;
	return false;
}

