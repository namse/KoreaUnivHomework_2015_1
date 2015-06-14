#include "stdafx.h"
#include "Triangle.h"
#include "RayTracingEngine.h"

Namse::Vector Namse::Triangle::GetCenter()
{
	return (*m_Vector[0] + *m_Vector[1] + *m_Vector[2]) / 3.0;
}



void Namse::Triangle::RotateBy(GLdouble _angleX, GLdouble _angleY, GLdouble _angleZ)
{
	auto center = GetCenter();

	MoveBy(-center);

	for (auto& vector : m_Vector)
		vector->RotateBy(_angleX, _angleY, _angleZ);

	MoveBy(center);
}

void Namse::Triangle::MoveBy(Vector _vector)
{
	for (auto& vector : m_Vector)
		vector->MoveBy(_vector);
}

void Namse::Triangle::OnDraw(Vector& BasePosition)
{
	Node::OnDraw(BasePosition);


	// TODO
	// Optimize - 필요한 경우에만 업데이트. 필요한지 아닌지는 Dirty Bit으로 확인.

	m_AbsolutePosition = m_Position + BasePosition;

	m_MinVector.m_X = std::min(std::min(m_Vector[0]->m_X, m_Vector[1]->m_X), m_Vector[2]->m_X) + m_AbsolutePosition.m_X;
	m_MinVector.m_Y = std::min(std::min(m_Vector[0]->m_Y, m_Vector[1]->m_Y), m_Vector[2]->m_Y) + m_AbsolutePosition.m_Y;
	m_MinVector.m_Z = std::min(std::min(m_Vector[0]->m_Z, m_Vector[1]->m_Z), m_Vector[2]->m_Z) + m_AbsolutePosition.m_Z;

	m_MaxVector.m_X = std::max(std::max(m_Vector[0]->m_X, m_Vector[1]->m_X), m_Vector[2]->m_X) + m_AbsolutePosition.m_X;
	m_MaxVector.m_Y = std::max(std::max(m_Vector[0]->m_Y, m_Vector[1]->m_Y), m_Vector[2]->m_Y) + m_AbsolutePosition.m_Y;
	m_MaxVector.m_Z = std::max(std::max(m_Vector[0]->m_Z, m_Vector[1]->m_Z), m_Vector[2]->m_Z) + m_AbsolutePosition.m_Z;
	
	g_RayTracingEngine->m_MinVector.m_X = std::min(g_RayTracingEngine->m_MinVector.m_X, m_MinVector.m_X);
	g_RayTracingEngine->m_MinVector.m_Y = std::min(g_RayTracingEngine->m_MinVector.m_Y, m_MinVector.m_Y);
	g_RayTracingEngine->m_MinVector.m_Z = std::min(g_RayTracingEngine->m_MinVector.m_Z, m_MinVector.m_Z);
	
	g_RayTracingEngine->m_MaxVector.m_X = std::max(g_RayTracingEngine->m_MaxVector.m_X, m_MaxVector.m_X);
	g_RayTracingEngine->m_MaxVector.m_Y = std::max(g_RayTracingEngine->m_MaxVector.m_Y, m_MaxVector.m_Y);
	g_RayTracingEngine->m_MaxVector.m_Z = std::max(g_RayTracingEngine->m_MaxVector.m_Z, m_MaxVector.m_Z);

	auto a = (*m_Vector[2] - *m_Vector[0]);
	auto b = (*m_Vector[1] - *m_Vector[0]);
	m_NormalVector = (*m_Vector[1] - *m_Vector[0]).CrossProduct(*m_Vector[2] - *m_Vector[0]).Unit();

	m_FirstVectorOnNormalVectorCoordination = m_NormalVector.DotProduct(*m_Vector[0] + m_AbsolutePosition);

	for (int i = 0; i < 3; i++)
	{
		m_NormalVectors[i] = m_NormalVector.CrossProduct(*m_Vector[(i + 1) % 3] - *m_Vector[i]).Unit();
		m_Distnace[i] = m_NormalVectors[i].DotProduct(*m_Vector[i]);
	}

	g_RayTracingEngine->PushTriangleToOctree(this);
}
