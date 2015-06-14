#pragma once
#include <atomic>

void Work(int xi, int yi);
#define ThreadWidth 2
#define ThreadHeight 2
extern unsigned int Sampling;
extern std::atomic<bool> WorkerWait[ThreadWidth * ThreadHeight];
extern bool AllWorkDown;