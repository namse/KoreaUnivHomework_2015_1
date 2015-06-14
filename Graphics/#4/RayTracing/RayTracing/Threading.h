#pragma once
#include <atomic>

void Work(int xi, int yi);
#define ThreadWidth 1
#define ThreadHeight 2
#define Sampling 2
extern std::atomic<bool> WorkerWait[ThreadWidth * ThreadHeight];
extern bool AllWorkDown;