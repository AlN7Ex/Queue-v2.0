// mall.c -- Use Queue interface
// Compile with queue.c
#include <stdio.h>
#include <stdlib.h>											// for rand() and srand()
#include <time.h>											// for time()
#include "queue.h"
#define MIN_PER_HOUR 60.0

bool newcustomer(double x);									// Have a new customer ? // use rand() for definition does customer appear in the current minute
Item customertime(long when);								// set customer parameters // set 'arrive' and 'proccestime' struct of 'temp'

int main(void)
{
	Queue line;
	Item temp;												// information about new client // variable of type Item describes new customer
	int hours;												// amount hours of modeling
	int perhour;											// average amount of clients arrive per hour
	double min_per_cust = 0;								// average amount of minutes between customers arrive
	long cycle, cyclelimit;									// counter and max cycle value
	long turnaways = 0;										// amount of arrived customer who have been denied service
	long customers = 0;										// amount of humans who queue up (oh, new phrasal verb :) )
	int wait_time = 0;										// remaining time when consultation will be finished
	long line_wait = 0;										// accumulated value of all spent time in line by all customers
	long served = 0;										// number of clients actually served
	long sum_line = 0;										// accumulated value of length of queue by current moment

	InitializeQueue(&line);									// 'line' as struct Queue, InititalizeQueue gets address of 'line', work by pointer
	srand((unsigned int) time(0));							// random rand() initialize
	puts("Example: consulting kiosk");+
	puts("Enter duration of modeling in hour");
	scanf("%d", &hours);
	cyclelimit = MIN_PER_HOUR * hours;
	puts("Enter average number of clients arrive per hour");
	scanf("%d", &perhour);
	min_per_cust = MIN_PER_HOUR / perhour;

	for (cycle = 0; cycle < cyclelimit; cycle++)
	{
		if (newcustomer(min_per_cust))
		{
			if (QueueIsFull(&line))
				turnaways++;
			else
			{
			customers++;
			temp = customertime(cycle);
			EnQueue(temp, &line);
			}
		}
		if (wait_time <= 0 && !QueueIsEmpty(&line))
		{
			DeQueue(&temp, &line);
			wait_time = temp.processtime;
			line_wait += cycle - temp.arrive;
			served++;
		}
		if (wait_time > 0)
			wait_time--;
		sum_line += QueueItemCount(&line);
	}
	if (customers > 0)
	{
		printf("		accepted clients: %ld\n", customers);
		printf("    served clients: %ld\n", served);
		printf("			denied: %ld\n", turnaways);
		printf(" average queue length: %.2f\n", (double)sum_line / cyclelimit);
		printf(" average waiting time: %.2f мин\n", (double)line_wait / served);
	}
	else
		puts("Have no clients!");
	EmptyTheQueue(&line);
	puts("Executed.");

	return 0;
}

// x - average time clients in minutes between arrive
// return true if client appears duration in current minute
bool newcustomer(double x)
{
	if (rand() * x / RAND_MAX < 1)
		return true;
	else
		return false;
}

// when - time of arrive client
// function return Item struct with time of arrive,
// which set in 'when' and time of served, which
// set by rand() value from 1 to 3
Item customertime(long when)
{
	Item cust;

	cust.proccestime = rand() % 3 + 1;
	cust.arrive = when;

	return cust;
}