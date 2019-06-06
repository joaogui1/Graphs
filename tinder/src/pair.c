#include <stdio.h>
#include <stdlib.h>
#include "pair.h"

Pair makePair(int first, int second) {
    Pair p;
    p.first = first;
    p.second = second;
    return p;
}

void printPair(Pair p) {
    printf("First: %d\tSecond: %d\n", p.first, p.second);
    return;
}