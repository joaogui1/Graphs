#ifndef PAIR_H
#define PAIR_H

typedef struct _pair {
    int first;
    int second;
} Pair;

Pair makePair(int first, int second);
void printPair(Pair p);

#endif