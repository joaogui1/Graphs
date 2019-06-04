#ifndef UTILS_H
#define UTILS_H

#include "adj_matrix.h"
#include "profile.h"

typedef struct _net {
    int treshold;
    int size;
    Profile profiles[maxSize];
    Graph* conexions;
} Net;

Net* initNet();
bool getProfile(Net* net, int* pos, int op);
void insertProfile(Net* net, Profile profile);
void createEdges(Net* net);
void sendInvitation(Net* net, int pos, int pos2);
void setAsFriends(Net* net, int yourPos, int friendPos);
void seeInvitations(Net* net, int pos);
void suggestProfile(Net* net, int pos);
void fakeFriends(Net* net, int pos);
void perfectMatch(Net* net, int pos);
void changeTreshold(Net* net);
void getDistance(Net* net, int pos, int pos2);
void getAllDistances(Net* net);
void printMat(int** mat, int size);
void getPrevious(Net* net, int pos, int pos2);
void printFriends(Net* net, int pos2);
void minCut(Net* net, int pos, int pos2);

#endif