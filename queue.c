//queue.c -- Realize interface

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

// Local functions
static void CopyToNode(Item item, Node * pn);
static void CopyToItem(Node * pn, Item * pi);

void InitializeQueue(Queue * pq)
{
	pq->front = pq->rear = NULL;
	pq->items = 0;
}

bool QueueIsFull(const Queue * pq)
{
	return pq->items == MAXQUEUE;
}

bool QueueIsEmpty(const Queue * pq)
{
	return pq->items == 0;
}

int QueueItemCount(const Queue * pq)
{ 
	return pq->items; 
}

bool EnQueue(Item item, Queue * pq)			// "Item" as just int types??
{
	Node * pnew;							// Need some explanation
	if (QueueIsFull(pq))					// What does 'pq' mean ??
											// How it's working? Is it formal param or actual arg? 
		return false;
	pnew = (Node *) malloc(sizeof(Node));	// Need some explanation
	if (pnew == NULL)
	{
		fprintf(stderr, "Can't allocate memory\n");
		exit(1);
	}
	CopyToNode(item, pnew);
	pnew->next = NULL;
	if (QueueIsEmpty(pq))
		pq->front = pnew;					// Element add to start of queue
	else
		pq->rear->next = pnew;				// Binding with end of queue
	pq->rear = pnew;						// Location end of queue
	pq->items++;							// Increase by 1 amount of elements in queue

	return true;
}

bool DeQueue(Item * pitem, Queue * pq)
{
	Node * pt;

	if (QueueIsEmpty(pq))
		return false;
	CopyToItem(pq->front, pitem);
	pt = pq->front;
	pq->front = pq->front->next;
	free(pt);
	pq->items--;
	if (pq->items == 0)
		pq->rear = NULL;

	return true;
}

void EmptyTheQueue(Queue * pq)
{
	Item dummy;

	while (!QueueIsEmpty(pq))
		DeQueue(&dummy, pq);
}

static void CopyToNode(Item item, Node * pn)
{
	pn->item = item;
}

static void CopyToItem(Node * pn, Item * pi)
{
	*pi = pn->item;
}