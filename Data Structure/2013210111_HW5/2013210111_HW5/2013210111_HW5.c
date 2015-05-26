#include <stdio.h>
#include <windows.h>
#include "container.h"

// this 'counter' code is from http://stackoverflow.com/questions/1739259/how-to-use-queryperformancecounter //
double PCFreq = 0.0;
__int64 CounterStart = 0;

void StartCounter()
{
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		printf("QueryPerformanceFrequency failed!\n");

	PCFreq = (double)(li.QuadPart) / 1000000.0;

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}
double GetCounter()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return (double)(li.QuadPart - CounterStart) / PCFreq;
}

// below code is from 2013210111 NamSeHyun

void InsertTest(int* inputData,
	int length,
	void* container,
	void(*insertFunction)(void* container, int value))
{
	for (int i = 0; i < length; i++)
	{
		insertFunction(container, inputData[i]);
	}
}

void DeleteTest(int* inputData,
	int length,
	void* container,
	void(*deleteFunction)(void* container, int value))
{
	for (int i = 0; i < length; i++)
	{
		deleteFunction(container, inputData[i]);
	}
}

void SearchTest(int* inputData,
	int length,
	void* container,
struct Node*(*searchFunction)(void* container, int value))
{
	for (int i = 0; i < length; i++)
	{
		searchFunction(container, inputData[i]);
	}
}

void Test(int* inputData,
	int length,
	void* container, 
	void(*insertFunction)(void* container, int value), 
	struct Node*(*searchFunction)(void* container, int value),
	void(*deleteFunction)(void* container, int value))
{
	printf("Length : %d\n", length);
	
	StartCounter();
	InsertTest(inputData, length, container, insertFunction);
	double microSecond = GetCounter();

	printf("Inserting : %.2f microSecond", microSecond);

	StartCounter();
	SearchTest(inputData, length, container, searchFunction);
	microSecond = GetCounter();

	printf("searching : %.2f microSecond", microSecond);

	StartCounter();
	DeleteTest(inputData, length, container, deleteFunction);
	microSecond = GetCounter();

	printf("deleting : %.2f microSecond", microSecond);
}
int main()
{

	return 0;
}