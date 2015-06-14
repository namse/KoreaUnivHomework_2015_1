#include "stdafx.h"
#include "Camera.h"
#include "GLMath.h"


Namse::Camera::Camera()
	:m_X(Namse::Vector(1.0, 0.0, 0.0)), m_Y(Namse::Vector(0.0, 1.0, 0.0)), m_Z(Namse::Vector(0.0, 0.0, 1.0))
	, m_Reference(Namse::Vector(0.0, 0.0, 0.0))
{
	m_Position = Namse::Vector(0.0, 0.0, 0.0);
}


Namse::Camera::~Camera()
{
}


void Namse::Camera::CalculateRayMatrix()
{
	mat4x4 Vin;
	Vin[0] = m_X.m_X; Vin[4] = m_Y.m_X; Vin[8] = m_Z.m_X;
	Vin[1] = m_X.m_Y; Vin[5] = m_Y.m_Y; Vin[9] = m_Z.m_Y;
	Vin[2] = m_X.m_Z; Vin[6] = m_Y.m_Z; Vin[10] = m_Z.m_Z;

	m_RayMatrix = Vin * m_Pin * BiasMatrixInverse * m_VPin;
}

void Namse::Camera::Look(const Namse::Vector &Position, const Namse::Vector &Reference, bool RotateAroundReference)
{
	m_Reference = Reference;
	m_Position = Position;

	m_Z = (-Reference+Position).Unit();
	m_X = (Namse::Vector(0.0f, 1.0f, 0.0f).CrossProduct(m_Z).Unit());
	m_Y = m_Z.CrossProduct(m_X);

	if (!RotateAroundReference)
	{
		m_Reference = m_Position;
		m_Position += m_Z * 0.05f;
	}

	CalculateRayMatrix();
}

bool Namse::Camera::OnKeyDown(unsigned int nChar)
{
	float Distance = 0.125f;

	
	Namse::Vector Up(0.0f, 1.0f, 0.0f);
	Namse::Vector Right = m_X;
	Namse::Vector Forward = Up.CrossProduct(Right);

	Up *= Distance;
	Right *= Distance;
	Forward *= Distance;

	Namse::Vector Movement;

	if (toupper(nChar) == 'W') Movement += Forward;
	if (toupper(nChar) == 'S') Movement -= Forward;
	if (toupper(nChar) == 'A') Movement -= Right;
	if (toupper(nChar) == 'D') Movement += Right;
	if (toupper(nChar) == 'R') Movement += Up;
	if (toupper(nChar) == 'F') Movement -= Up;

	m_Reference += Movement;
	m_Position += Movement;

	return Movement.m_X != 0.0f || Movement.m_Y != 0.0f || Movement.m_Z != 0.0f;
}

void Namse::Camera::OnMouseMove(int dx, int dy)
{
	float sensitivity = 0.25f;

	float hangle = (float)dx * sensitivity;
	float vangle = (float)dy * sensitivity;

	m_Position -= m_Reference;

	m_Y = rotate(m_Y, vangle, m_X);
	m_Z = rotate(m_Z, vangle, m_X);

	if (m_Y.m_Y < 0.0f)
	{
		m_Z = Namse::Vector(0.0f, m_Z.m_Y > 0.0f ? 1.0f : -1.0f, 0.0f);
		m_Y = m_Z.CrossProduct(m_X);
	}

	m_X = rotate(m_X, hangle, Namse::Vector(0.0f, 1.0f, 0.0f));
	m_Y = rotate(m_Y, hangle, Namse::Vector(0.0f, 1.0f, 0.0f));
	m_Z = rotate(m_Z, hangle, Namse::Vector(0.0f, 1.0f, 0.0f));

	m_Position = m_Reference + m_Z * m_Position.Norm();

	CalculateRayMatrix();
}

void Namse::Camera::OnReshpae(int w, int h)
{
	m_VPin[0] = 1.0f / (float)w;
	m_VPin[5] = 1.0f / (float)h;

	float tany = tan(45.0f / 360.0f * (float)M_PI);
	float aspect = (float)w / (float)h;

	m_Pin[0] = tany * aspect;
	m_Pin[5] = tany;
	m_Pin[10] = 0.0f;
	m_Pin[14] = -1.0f;

	CalculateRayMatrix();
}
