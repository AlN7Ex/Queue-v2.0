
//queue.h -- queue inteface
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdbool.h>
#define MAXQUEUE 10

typedef int item
{
	long arrive;								// time when a person gets in line
	int processtime;							// desired number of minutes of consultation
} Item;

typedef struct node
{
	Item item;
	struct node * next;
} Node;

typedef struct queue
{
	Node * front;
	Node * rear;
	int items;
} Queue;

void InitializeQueue (Queue * pq);			// Empty initialize 
bool QueueIsFull (const Queue *pq);			// Check for fill
bool QueueIsEmpty (const Queue * pq);		// Check for empty
int QueueItemCount (const Queue * pq);		// Definition amount of elements in queue 
bool EnQueue (Item item, Queue * pq);		// Add element in the end of queue
bool DeQueue (Item * pitem, Queue * pq);	// Delete element from start of queue
void EmptyTheQueue (Queue * pq);			// Erase queue

#endif