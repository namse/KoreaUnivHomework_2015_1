#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"


typedef struct Status
{
	int m_ServedCustomerNumber;
	int m_TotalServiceTime;
	int m_totalWaitTime;
	int m_MaxQueueSize;

	int m_LastServiceStartTime;
	int m_LastServiceTimeRequired;
};



void NewCustomer(struct Queue* queue, int clock)
{
	static int customerNumber = 0;
	int random = rand() % 4; // 0, 1, 2, 3
	if (random == 0) // 1/4 probability
	{
		customerNumber++;
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		if (newNode == NULL)
		{
			printf("Malloc for new Node Error\n");
			exit(-1);
		}
		newNode->m_ArriveTime = clock;
		newNode->m_CustomerNumber = customerNumber;
		newNode->next = NULL;
		PushBack(queue, newNode);
	}
}

void ServeStart(struct Queue* queue, int clock, struct Status* status, struct Node** currentServingCustomer)
{
	if (clock < status->m_LastServiceStartTime + status->m_LastServiceTimeRequired)
	{
		// Not Yet. Im working!
		return;
	}
	else
	{
		// IDLE
		
		if (GetCurrentQueueSize(queue) == 0) // is empty?
			return;
		else
		{
			struct Node* customer = PopFront(queue);
			int serviceTime = (rand() % 10) + 1;
			int currentQueueSize = GetCurrentQueueSize(queue);

			status->m_ServedCustomerNumber++;
			status->m_TotalServiceTime += serviceTime;
			status->m_totalWaitTime += clock - customer->m_ArriveTime;
			status->m_MaxQueueSize = currentQueueSize > status->m_MaxQueueSize ? currentQueueSize : status->m_MaxQueueSize;
			status->m_LastServiceStartTime = clock;
			status->m_LastServiceTimeRequired = serviceTime;

			customer->m_ServiceStartTime = clock;
			customer->m_ServiceTime = serviceTime;
			*currentServingCustomer = customer;

		}
	}
}

void OnServeFinished(struct Queue* queue, int clock, struct Status* status, struct Node** customer)
{
	if (clock == status->m_LastServiceStartTime + status->m_LastServiceTimeRequired)
	{
		// Yes! Serving is just Finished!!
		printf("灰Customer No. %d\n"
			"朵式Arrive Time			: %02d:%02d\n"
			"朵式Service Start Time		: %02d:%02d\n"
			"朵式Service Time		: %2d Minute(s)\n"
			"朵式Customer Wait Time		: %3d Minute(s)\n"
			"汍式Current Queue Size		: %2d\n\n"
			, (*customer)->m_CustomerNumber
			, (*customer)->m_ArriveTime / 60, (*customer)->m_ArriveTime % 60
			, (*customer)->m_ServiceStartTime / 60, (*customer)->m_ServiceStartTime % 60
			, (*customer)->m_ServiceTime
			, (*customer)->m_ServiceStartTime - (*customer)->m_ArriveTime
			, GetCurrentQueueSize(queue)
			);

		free((*customer));
		(*customer) = NULL;
		return;
	}
}

void main()
{
	srand(time(NULL));
	int nowClock = 9 * 60 + 0; // 09:00
	struct Queue* myQueue = CreateQueue();
	struct Status myStatus;
	struct Node* currentServingCustomer = NULL;

	myStatus.m_ServedCustomerNumber = 0,
		myStatus.m_TotalServiceTime = 0,
		myStatus.m_totalWaitTime = 0,
		myStatus.m_MaxQueueSize = 0,
		myStatus.m_LastServiceStartTime = 0,
		myStatus.m_LastServiceTimeRequired = 0;

	if (myQueue == NULL)
	{
		printf("Create Queue Error!\n");
		exit(-1);
	}

	for (nowClock = 9 * 60 + 0; // 09:00
		(nowClock <= 17 * 60 + 0 // 17:00
		|| currentServingCustomer != NULL);
	nowClock++)
	{
		if (nowClock <= 17 * 60 + 0)
			NewCustomer(myQueue, nowClock);
		OnServeFinished(myQueue, nowClock, &myStatus, &currentServingCustomer);
		ServeStart(myQueue, nowClock, &myStatus, &currentServingCustomer);
	}


	printf("灰Simultation Statistics\n"
		"朵式Total Customer		: %d\n"
		"朵式Total Service Time		: %02d Hours %02d Minutes\n"
		"朵式Average Service Time	: %.2f Minute(s)\n"
		"朵式Average Wait Time		: %.2f Minute(s)\n"
		"朵式Maximum Queue Size		: %d\n"
		"汍式Closed Time			: %02d:%02d\n\n"
		, myStatus.m_ServedCustomerNumber
		, myStatus.m_TotalServiceTime / 60, myStatus.m_TotalServiceTime % 60
		, ((double)myStatus.m_TotalServiceTime /  (double)myStatus.m_ServedCustomerNumber)
		, ((double)myStatus.m_totalWaitTime / (double)myStatus.m_ServedCustomerNumber)
		, myStatus.m_MaxQueueSize
		, (nowClock-1)/60, (nowClock-1)%60
		);

	free(myQueue);
	printf("press any key to exit");
	getch();
	return;
}