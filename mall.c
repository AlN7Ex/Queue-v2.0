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
	long turnaways = 0;										// amount of arrived customer who have been denied service
	long customers = 0;										// amount of humans who queue up (oh, new phrasal verb :) )
	int wait_time = 0;										// remaining time when consultation will be finished
	long line_wait = 0;										// accumulated value all spent time in line by all customers
	long served = 0;										// number of clients actually served
	long sum_line = 0;										// accumulated value length of queue by current moment

	InitializeQueue(&line);
	srand((unsigned int) time(0));

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
}