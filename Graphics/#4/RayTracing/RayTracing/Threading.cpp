#include "stdafx.h"
#include "Threading.h"
#include "RayTracingEngine.h"
#include <iostream>
extern std::atomic<bool> WorkerWait[ThreadWidth * ThreadHeight] = { true, };
extern bool AllWorkDown = false;
unsigned int Sampling = 1;
void Work(int xi, int yi)
{
	printf("%d,%d\n", xi, yi);
	while (!AllWorkDown)
	{
		while (WorkerWait[xi + yi * ThreadWidth])
		{
			//std::cout << xi << "/" << yi << "|-Waiting" << std::endl;
		}
		
		auto width = g_RayTracingEngine->m_WindowWidth / (float)ThreadWidth;
		auto height = g_RayTracingEngine->m_WindowHeight / (float)ThreadHeight;

		for (int y = yi * height; y < (yi + 1) * height; y++)
		{
			for (int x = xi * width; x < (xi + 1) * width; x++)
			{
				if (x == 67 && y == 56)
				{
					int a = 5;
				}
				Namse::Color color;
				for (int dx = 1; dx <= Sampling; dx++)
				{
					for (int dy = 1; dy <= Sampling; dy++)
					{
						//std::cout << xi << "/" << yi << "|-[" << x << "," << y << "]"<<std::endl;
						vec4 rayVec4(g_RayTracingEngine->m_Camera.m_RayMatrix * vec4((float)x + (1.f / ((float)Sampling+1.f)) * dx, (float)y + (1.f / ((float)Sampling+1.f)) * dy, 0.0f, 1.0f));

						Namse::Vector rayVec(rayVec4.x, rayVec4.y, rayVec4.z);

						color += g_RayTracingEngine->RayTrace(g_RayTracingEngine->m_Camera.m_Position, rayVec.Unit());
					}
				}
				g_RayTracingEngine->m_ColorBuffer[x + y * g_RayTracingEngine->m_WindowWidth]
					= color / (Sampling * Sampling);
			}
		}
		WorkerWait[xi + yi * ThreadWidth] = true;
		//std::cout << xi << "/" << yi << "|-Finished#############" << std::endl;
	}
}