#pragma once
#include <atomic>

void Work(int xi, int yi);
#define ThreadWidth 1
#define ThreadHeight 3
extern std::atomic<bool> WorkerWait[ThreadWidth * ThreadHeight];
extern bool AllWorkDown;