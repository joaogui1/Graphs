#ifndef QUEUE_H
#define QUEUE_H

#include "pair.h"
#include <stdbool.h>

typedef struct _node {
    Pair p;
    struct _node* next;
} Node;

typedef struct _queue {
    int size;
    Node* begin;
    Node* end;
} Queue;

Queue* createQueue();
void insertQueue(Queue* q, int first, int second);
Pair popQueue(Queue* q);
bool isEmptyQueue(Queue* q);
void printQueue(Queue* q);
void testQueue();

#endif