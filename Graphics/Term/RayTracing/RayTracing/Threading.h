#pragma once
#include <atomic>

void Work(int xi, int yi);
#define ThreadWidth 1
#define ThreadHeight 3
extern unsigned int Sampling;
extern std::atomic<bool> WorkerWait[ThreadWidth * ThreadHeight];
extern bool AllWorkDown;