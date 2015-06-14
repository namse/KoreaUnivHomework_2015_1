#include "stdafx.h"
#include "Threading.h"
#include "RayTracingEngine.h"
#include <iostream>
extern std::atomic<bool> WorkerWait[ThreadWidth * ThreadHeight] = { true, };
extern bool AllWorkDown = false;
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
				//std::cout << xi << "/" << yi << "|-[" << x << "," << y << "]"<<std::endl;
				vec4 rayVec4(g_RayTracingEngine->m_Camera.m_RayMatrix * vec4((float)x + 0.5f, (float)y + 0.5f, 0.0f, 1.0f));

				Namse::Vector rayVec(rayVec4.x, rayVec4.y, rayVec4.z);

				g_RayTracingEngine->m_ColorBuffer[x + y * g_RayTracingEngine->m_WindowWidth] 
					= g_RayTracingEngine->RayTrace(g_RayTracingEngine->m_Camera.m_Position, rayVec.Unit(), 1);
			}
		}
		WorkerWait[xi + yi * ThreadWidth] = true;
		//std::cout << xi << "/" << yi << "|-Finished#############" << std::endl;
	}
}