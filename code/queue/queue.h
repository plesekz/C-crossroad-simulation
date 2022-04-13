#ifndef __QUEUE
#define __QUEUE

/* imports */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* structure definition */
struct stackNode {
	struct stackNode* next;
	void* value;
};

struct stackRoot{
	struct stackNode* first;
	struct stackNode* last;
	int elements;
};

typedef struct stackNode QUEUENODE;
typedef struct stackRoot ROOT;

/* function prototypes */

ROOT* newQueue();
void push(ROOT* r, void* v);
void* pop(ROOT* r);
void emptyQueue(ROOT* r);
bool isEmpty(ROOT* r);

#endif