#include "stdafx.h"
#include "RayTracingEngine.h"

Namse::RayTracingEngine* g_RayTracingEngine = nullptr;

Namse::RayTracingEngine::RayTracingEngine()
	:m_Octree(), m_ColorBuffer(nullptr), m_IsReshapeReserved(false), m_ReservedHopCount(MAX_RAY_HOP)
{
	m_RootNode.m_Position = Namse::Vector(0, 0, 0);
	m_MaxVector.m_X = m_MaxVector.m_Y = m_MaxVector.m_Z = std::numeric_limits<double>::min();
	m_MinVector.m_X = m_MinVector.m_Y = m_MinVector.m_Z = std::numeric_limits<double>::max();
}


Namse::RayTracingEngine::~RayTracingEngine()
{
	AllWorkDown = true;
	for (auto& thread : m_Threads)
		thread.join();

	if (m_ColorBuffer != nullptr)
		delete m_ColorBuffer;
}

void Namse::RayTracingEngine::PushTriangleToOctree(Triangle* triangle)
{
	m_Octree.Add(triangle);
}

void Namse::RayTracingEngine::Reshape(int w, int h)
{
	if (m_ColorBuffer && sizeof(Namse::Color) * w * h > m_BufferSize)
	{
		delete m_ColorBuffer;
		m_ColorBuffer = nullptr;
	}
	if (m_ColorBuffer == nullptr)
	{
		m_ColorBuffer = (Namse::Color*)malloc(sizeof(Color) * w * h);
		m_BufferSize = sizeof(float) * w * h * 3;
	}

	m_WindowWidth = w;
	m_WindowHeight = h;

	m_Camera.OnReshpae(w, h);

	m_IsReshapeReserved = false;
}
void Namse::RayTracingEngine::ReserveReshape(int w, int h)
{
	m_IsReshapeReserved = true;
	m_ReservedWidth = w;
	m_ReservedHeight = h;
}

void Namse::RayTracingEngine::OnDisplay()
{
	if (m_IsReshapeReserved)
	{
		Reshape(m_ReservedWidth, m_ReservedHeight);
	}
	MAX_RAY_HOP = m_ReservedHopCount;
	if (m_ColorBuffer != nullptr)
	{
		// 1. reset octree
		// 
		m_Octree.Reset(Namse::Vector(0.f, 0.f, 0.f), 4 * std::min(std::min((m_MaxVector - Namse::Vector(0.f, 0.f, 0.f)).Norm(), (m_MinVector - Namse::Vector(0.f, 0.f, 0.f)).Norm()), MAX_DISTNACE));

		double a = (m_MaxVector - m_MinVector).Norm();
		m_MaxVector.m_X = m_MaxVector.m_Y = m_MaxVector.m_Z = std::numeric_limits<double>::min();
		m_MinVector.m_X = m_MinVector.m_Y = m_MinVector.m_Z = std::numeric_limits<double>::max();

		// 2. push nodes to octree
		m_RootNode.OnDraw(Namse::Vector(0.f, 0.f, 0.f));

		// 3. Ray Trace start

		for (int y = 0; y < ThreadHeight; y++)
		{
			for (int x = 0; x < ThreadWidth; x++)
			{
				WorkerWait[x + y * ThreadWidth] = false;
			}
		}

		while (true)
		{
			bool workerFinish = true;
			for (int i = 0; i < ThreadHeight * ThreadWidth; i++)
			{
				if (!WorkerWait[i])
					workerFinish = false;
			}

			if (workerFinish == true)
				break;
		}


		glDrawPixels(m_WindowWidth, m_WindowHeight, GL_RGB, GL_FLOAT, m_ColorBuffer);
	}
	printf("%d\n", glutGet(GLUT_ELAPSED_TIME));
}

void Namse::RayTracingEngine::AddChild(Node* node)
{
	m_RootNode.AddChild(node);
}

void Namse::RayTracingEngine::RemoveChild(Node* node)
{
	m_RootNode.RemoveChild(node);
}

Namse::Color Namse::RayTracingEngine::RayTrace(Namse::Triangle* triangle, Namse::Vector& contactPoint, Namse::Vector& ray, unsigned int currentHop)
{
	Color retColor;
	GLdouble distance;
	Namse::Vector tempContactPoint;
	Namse::Triangle* tempTriangle = nullptr;


	if (currentHop >= MAX_RAY_HOP)
		return retColor;

	// reflection
	Namse::Vector reflectionVector = ray + triangle->m_NormalVector * (ray.DotProduct(-triangle->m_NormalVector)) * 2.f;
	if (m_Octree.FindNearestTriangle(contactPoint, reflectionVector, MAX_DISTNACE,
		distance, tempContactPoint, &tempTriangle))
	{
		retColor = RayTrace(tempTriangle, tempContactPoint, reflectionVector, currentHop + 1) * tempTriangle->m_ReflectionFactor;
	}


	// transmission
	// ½º³ÚÀÇ ¹ýÄ¢ ¾È¾¸
	Namse::Vector transmissionVector = ray;
	if (m_Octree.FindNearestTriangle(contactPoint, transmissionVector, MAX_DISTNACE,
		distance, tempContactPoint, &tempTriangle))
	{
		retColor = RayTrace(tempTriangle, tempContactPoint, transmissionVector, currentHop + 1) * tempTriangle->m_TransmissionFactor;
	}


	// to light

	for (auto& light : m_LightList)
	{
		switch (light->m_LightType)
		{
		case SPOT_LIGHT:
		{
			Namse::Vector toLightRay = (light->m_Position - contactPoint).Unit();
			auto dot = toLightRay.DotProduct(triangle->m_NormalVector);

			if (dot <= 0)
				break;

			Namse::Triangle* shadowMaker;
			GLdouble shadowMakerDistance;
			Namse::Vector shadowPoint;

			if (m_Octree.FindNearestTriangle(contactPoint, (light->m_Position - contactPoint).Unit()
				, (light->m_Position - contactPoint).Norm() + MIN_DISTNACE, shadowMakerDistance, shadowPoint, &shadowMaker))
			{
				retColor += RayTrace(shadowMaker, shadowPoint, (light->m_Position - contactPoint).Unit(),
					currentHop + 1) * shadowMaker->m_TransmissionFactor;
			}
			else
			{
				auto lightDistance = (contactPoint - light->m_Position).Norm();
				if (lightDistance != 0)
					retColor += light->m_Color * (dot)* light->m_LightPower / (lightDistance);
			}
		}break;
		case DIRECTIONAL_LIGHT:
		{
			Namse::Triangle* shadowMaker;
			GLdouble shadowMakerDistance;
			Namse::Vector shadowPoint;

			Namse::Vector lightRay = -((Namse::DirectionalLight*)(light))->m_Ray;
			auto dot = lightRay.DotProduct(triangle->m_NormalVector);
			if (dot <= 0)
				break;

			if (m_Octree.FindNearestTriangle(contactPoint, -((Namse::DirectionalLight*)(light))->m_Ray
				, distance, shadowMakerDistance, shadowPoint, &shadowMaker))
			{
				retColor += RayTrace(shadowMaker, shadowPoint, (light->m_Position - contactPoint).Unit(),
					currentHop + 1) * shadowMaker->m_TransmissionFactor;
			}
			else
			{
				retColor += light->m_Color * dot * light->m_LightPower;
			}
		}break;
		}
	}



	return retColor;

}

Namse::Color Namse::RayTracingEngine::RayTrace(Namse::Vector& from, Namse::Vector& ray)
{
	Color retColor;
	GLdouble distance;
	Namse::Vector contactPoint;
	Namse::Triangle* triangle = nullptr;

	if (m_Octree.FindNearestTriangle(from, ray, MAX_DISTNACE,
		distance, contactPoint, &triangle))
	{
		retColor = RayTrace(triangle, contactPoint, ray, 1);
	}
	return retColor;

}

void Namse::RayTracingEngine::ThreadSetup()
{
	memset(WorkerWait, true, sizeof(WorkerWait));
	AllWorkDown = false;

	for (int y = 0; y < ThreadHeight; y++)
	{
		for (int x = 0; x < ThreadWidth; x++)
		{
			m_Threads[x + y * ThreadWidth] = std::thread(Work, x, y);
		}
	}
}


bool Namse::RayTracingEngine::OnKeyDown(unsigned int nChar)
{
	if (toupper(nChar) == 'P') m_ReservedHopCount++;
	if (toupper(nChar) == 'O') m_ReservedHopCount--;


	m_Camera.OnKeyDown(nChar);

	return true;
}
