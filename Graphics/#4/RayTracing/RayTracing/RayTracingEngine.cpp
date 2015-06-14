#include "stdafx.h"
#include "RayTracingEngine.h"

Namse::RayTracingEngine* g_RayTracingEngine = nullptr;

Namse::RayTracingEngine::RayTracingEngine()
	:m_Octree(), m_ColorBuffer(nullptr)
{
	m_RootNode.m_Position = Namse::Vector(0, 0, 0);
	m_MaxVector.m_X = m_MaxVector.m_Y = m_MaxVector.m_Z = std::numeric_limits<double>::min();
	m_MinVector.m_X = m_MinVector.m_Y = m_MinVector.m_Z = std::numeric_limits<double>::max();
}


Namse::RayTracingEngine::~RayTracingEngine()
{
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
	}
	if (m_ColorBuffer == nullptr)
	{
		m_ColorBuffer = (Namse::Color*)malloc(sizeof(Color) * w * h);
		m_BufferSize = sizeof(float) * w * h * 3;
	}

	m_WindowWidth = w;
	m_WindowHeight = h;

	m_Camera.OnReshpae(w, h);

}

void Namse::RayTracingEngine::OnDisplay()
{
	if (m_ColorBuffer != nullptr)
	{
		// 1. reset octree
		// 
		m_Octree.Reset(Namse::Vector(0.f, 0.f, 0.f), std::min((m_MaxVector - m_MinVector).Norm(), MAX_DISTNACE));

		double a = (m_MaxVector - m_MinVector).Norm();
		m_MaxVector.m_X = m_MaxVector.m_Y = m_MaxVector.m_Z = std::numeric_limits<double>::min();
		m_MinVector.m_X = m_MinVector.m_Y = m_MinVector.m_Z = std::numeric_limits<double>::max();

		// 2. push nodes to octree
		m_RootNode.OnDraw(Namse::Vector(0.f,0.f,0.f));

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

		/*
		for (int y = 0; y < m_WindowHeight; y++)
		{
			for (int x = 0; x < m_WindowWidth; x++)
			{
				vec4 rayVec4 (m_Camera.m_RayMatrix * vec4((float)x + 0.5f, (float)y + 0.5f, 0.0f, 1.0f));

				Namse::Vector rayVec(rayVec4.x, rayVec4.y, rayVec4.z);

				m_ColorBuffer[x + y * m_WindowWidth] = RayTrace(m_Camera.m_Position,
				rayVec.Unit(),
				1);
				//printf("################\n");
			}
		}*/

		glDrawPixels(m_WindowWidth, m_WindowHeight, GL_RGB, GL_FLOAT, m_ColorBuffer);
	}
	printf("%d\n",glutGet(GLUT_ELAPSED_TIME));
}

void Namse::RayTracingEngine::AddChild(Node* node)
{
	m_RootNode.AddChild(node);
}

void Namse::RayTracingEngine::RemoveChild(Node* node)
{
	m_RootNode.RemoveChild(node);
}

Namse::Color Namse::RayTracingEngine::RayTrace(Namse::Vector& from, Namse::Vector& ray, unsigned int currentHop)
{
	Color retColor;
	GLdouble distance;
	Namse::Vector contactPoint;
	Namse::Triangle* triangle = nullptr;
	
	if (m_Octree.FindNearestTriangle(from, ray, MAX_DISTNACE,
		distance, contactPoint, &triangle))
	{
		// light
		for (auto& light : m_LightList)
		{
			Namse::Triangle* shadowMaker;
			GLdouble shadowMakerDistance;
			Namse::Vector shadowPoint;
			
			if (m_Octree.FindNearestTriangle(triangle->m_Position, light->m_Position - triangle->m_Position
				, distance, shadowMakerDistance, shadowPoint, &shadowMaker))
			{
				if (currentHop < MAX_RAY_HOP)
				{
					retColor += RayTrace(shadowPoint,
						light->m_Position - triangle->m_Position,
						currentHop + 1) * shadowMaker->m_TransmissionFactor;
				}
			}
			else
			{
				retColor += light->m_Color * light->m_LightPower / (distance * distance);
			}
		}
		
		if (currentHop < MAX_RAY_HOP)
		{
			// reflection
			Namse::Vector reflectionVector = ray + triangle->m_NormalVector * (ray.DotProduct(-triangle->m_NormalVector)) * 2.f;
			retColor += RayTrace(contactPoint, ray, currentHop + 1) * triangle->m_ReflectionFactor;

			// transmission
			// ½º³ÚÀÇ ¹ýÄ¢ ¾È¾¸
			Namse::Vector transmissionVector = ray;
			retColor += RayTrace(contactPoint, ray, currentHop + 1) * triangle->m_TransmissionFactor;
		}
	}
	else{
		int a = 5;
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