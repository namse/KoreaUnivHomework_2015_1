#include <stdio.h>
#include <windows.h>
#include <time.h>
#include "BST.h"
#include "LinearList.h"

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
	void*(*searchFunction)(void* container, int value))
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
	void*(*searchFunction)(void* container, int value),
	void(*deleteFunction)(void* container, int value),
	double* pInsertTime,
	double* pSearchTime,
	double* pDeleteTime)
{
	printf("Length : %d\n", length);
	
	StartCounter();
	InsertTest(inputData, length, container, insertFunction);
	*pInsertTime = GetCounter();

	printf("Inserting : %.2f microSecond\n", *pInsertTime);

	StartCounter();
	SearchTest(inputData, length, container, searchFunction);
	*pSearchTime = GetCounter();

	printf("searching : %.2f microSecond\n", *pSearchTime);

	StartCounter();
	DeleteTest(inputData, length, container, deleteFunction);
	*pDeleteTime = GetCounter();

	printf("deleting : %.2f microSecond\n", *pDeleteTime);
}
int main()
{
	srand(time(NULL));

	int *inputData = NULL;
	int prevLength = 0;

	while (1)
	{
		int length, dataType;

		// 1. get length of data.
		printf("(exit : -1), Length of Data : ");
		scanf("%d", &length);

		if (length == -1)
			break;
		else if (length <= 0)
		{
			printf("wrong length.\n");
			continue;
		}

		// 2. alloc memory if you need.
		if (prevLength < length)
		{
			free(inputData);
			inputData = (int*)malloc(length * sizeof(int));
			prevLength = length;
		}

		// 3. get type of data.
		printf("1. Manual | 2. Random | 3. Sequence \n : ");
		scanf("%d", &dataType);

		// 4. set data.
		switch (dataType)
		{
		case 1:
		{
			for (int i = 0; i < length; i++)
			{
				int data;
				scanf("%d", &data);
				inputData[i] = data;
			}
		}break;
		case 2:
		{
			for (int i = 0; i < length; i++)
			{
				inputData[i] = rand();
			}
		}break;
		case 3:
		{
			for (int i = 0; i < length; i++)
			{
				inputData[i] = i;
			}
		}break;
		default:
			printf("wrong data type.\n");
			continue;
			break;
		}

		// 5. test them.

		double BSTInsertTime;
		double BSTSearchTime;
		double BSTDeleteTime;
		double LinearListInsertTime;
		double LinearListSearchTime;
		double LinearListDeleteTime;

		struct BST* bst = BST_Craete();
		struct LinearList* list = LinearList_Craete();

		// test bst
		printf("-- BST Test --\n");
		Test(inputData, length, bst, BST_Insert, BST_Search, BST_Delete, &BSTInsertTime, &BSTSearchTime, &BSTDeleteTime);

		// test linear list
		printf("-- LinearList Test --\n");
		Test(inputData, length, list, LinearList_Insert, LinearList_Search, LinearList_Delete, &LinearListInsertTime, &LinearListSearchTime, &LinearListDeleteTime);

		BST_Destory(bst);
		LinearList_Destroy(list);


		// 6. save test data.
		static int TestNumber = 0;
		char outputFileName[64] = "";
		sprintf(outputFileName, "output_%d.txt", TestNumber);
		FILE *fout = fopen(outputFileName, "w");
		
		fprintf(fout, "-- input Data --\n");
		for (int i = 0; i < length; i++)
		{
			fprintf(fout, "%d\n", inputData[i]);
		}

		fprintf(fout, "\n\n -- BST -- \n"
			"Insert : %.2f\n"
			"Search : %.2f\n"
			"Delete : %.2f\n\n", BSTInsertTime, BSTSearchTime, BSTDeleteTime);

		fprintf(fout, "\n\n -- LinearList -- \n"
			"Insert : %.2f\n"
			"Search : %.2f\n"
			"Delete : %.2f\n\n", LinearListInsertTime, LinearListSearchTime, LinearListDeleteTime);
		
		fclose(fout);

		TestNumber++;

		printf("\n\n");
	}

	free(inputData);
	return 0;
}