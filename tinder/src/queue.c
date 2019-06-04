#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "queue.h"

Node* createNode(int first, int second) {
    Node* n = calloc(1, sizeof(Node));
    
    n->p = makePair(first, second);
    n->next = NULL;
    
    return n;
}

Queue* createQueue() {
    Queue* q = calloc(1, sizeof(Queue));
    q->begin = createNode(-1, -1);
    q->end = NULL;
    q->size = 0;
    
    return q;
}

void insertQueue(Queue* q, int first, int second) {
    Node* newNode = createNode(first, second);
    if(newNode == NULL) return;
    
    if(q->end == NULL) {
        q->begin->next = newNode;
        q->end = newNode;
    }
    else {
        q->end->next = newNode;
        q->end = newNode;
    }

    (q->size)++;
    
    return;
}

Pair popQueue(Queue* q) {
    Pair p = makePair(-1, -1);

    if(q->size == 0) return p;
    
    p = q->begin->next->p;
    
    Node* temp = q->begin->next;
    q->begin->next = q->begin->next->next;
    if(temp != NULL) free(temp);
    
    (q->size)--;
    if(q->size == 0) q->end = NULL;

    return p;
}

bool isEmptyQueue(Queue* q) {
    return (q->size == 0);
}

void printQueue(Queue* q) {
    Node* curr = q->begin;
    while(curr != NULL) {
        printPair(curr->p);
        curr = curr->next;
    }
    return;
}

void recursiveDestroy(Node* curr) {
    if(curr == NULL) return;
    recursiveDestroy(curr->next);
    free(curr);
}

void destroyQueue(Queue* q) {
    Node* curr = q->begin->next;
    recursiveDestroy(curr);
    free(q->begin);
    free(q);
}

void testQueue() {
    Queue* q = createQueue();
    insertQueue(q, 1, 4);
    insertQueue(q, 2, 5);
    insertQueue(q, 3, 6);
    printf("%d\n", isEmptyQueue(q));
    printQueue(q);
    printf("\n");
    popQueue(q);
    popQueue(q);
    popQueue(q);
    popQueue(q);
    printf("%d\n", isEmptyQueue(q));
    printQueue(q);
    destroyQueue(q);
    return;
}