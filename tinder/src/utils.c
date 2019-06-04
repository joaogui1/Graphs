#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

Net* initNet() {
    int error = 0;
    Net* net = calloc(1, sizeof(Net));
    net->conexions = createGraphMatrix(&error);
    net->size = 0;
    net->treshold = 7;
    if(error) return NULL;
    return net;
}

bool getProfile(Net* net, int* pos, int op) {
    char name[300];
    
    if(op == 1) printf("What's your name?\n");
    else if(op == 2) printf("What's his/her name?\n");

    scanf(" %[^\r\n]", name);
    
    *pos = searchProfile(net->profiles, name, net->size);
    if(*pos == -1) {
        printf("This profile doesn't exist\n");
        return false;
    }

    return true;
}

void insertProfile(Net* net, Profile profile) {
    if(net->size == maxSize) return;

    net->profiles[net->size] = profile;
    net->size++;
    
    createEdges(net);

    return;
}

void createEdges(Net* net) {
    int error = 0;
    int lastNode = net->size-1;
    
    for (int i = 0; i < lastNode; i++) {
        int proximity = getProximity(net->profiles[i], net->profiles[lastNode]);
        addEdgeMatrix(net->conexions, i, lastNode, proximity, &error);
    }
    
    net->conexions->currSize++;

}

void sendInvitation(Net* net, int pos, int pos2) {
    if(pos == pos2) {
        printf("Why do you want to become friends with yourself??\n");
        return;
    }

    net->conexions->edges[pos][pos2].relation = sendRequest;
    net->conexions->edges[pos2][pos].relation = wasRequested;

    printf("Your invitations has been sent\n");
}

void setAsFriends(Net* net, int yourPos, int friendPos) {
    net->conexions->edges[yourPos][friendPos].relation = friends;
    net->conexions->edges[friendPos][yourPos].relation = friends;

    printf("You're friends now!\n");
    return;
}

void seeInvitations(Net* net, int pos) {
    bool found = false;
    char op;

    for (int i = 0; i < net->size; i++) {
        if(net->conexions->edges[pos][i].relation == wasRequested) {
            if(!found) {
                printf("Your invitations are: \n");
                found = true;
            }

            printProfile(net->profiles[i]);
            printf("Do you want to accept %s's invitation? (y or n)\n", net->profiles[i].name);
            scanf(" %c", &op);
            printf("\n");
            if(op == 'y') setAsFriends(net, i, pos);
        }
    }

    if(!found) printf("You have no invitations\n");

    return;
}

void suggestProfile(Net* net, int pos) {
    bool found = false;
    for(int i = 0; i < net->size; i++) {
        if(net->conexions->edges[pos][i].proximity >= net->treshold && net->conexions->edges[pos][i].relation != friends) {
            if(!found) {
                printf("\nSome possible friends are: \n");
                found = true;
            }
            
            printProfile(net->profiles[i]);
            printf("\n");
        }
    }

    if(!found) printf("No one is good for you =(\n");
    return;

    return;
}

void fakeFriends(Net* net, int pos) {
    bool found = false;
    int amountFriends = 0;
    
    for (int i = 0; i < net->size; i++) {
        if (net->conexions->edges[pos][i].relation == friends) amountFriends++;

        if(net->conexions->edges[pos][i].proximity < net->treshold && net->conexions->edges[pos][i].relation == friends) {
            if(!found) {
                printf("\nYour fake friends are: \n");
                found = true;
            }

            printProfile(net->profiles[i]);
            printf("\n");
        }
    }

    if(!found && amountFriends != 0) printf("You have only good friends, my friend\n");
    else if(!found && amountFriends == 0) printf("You have no friends =(\n");
    
    return;
}

void perfectMatch(Net* net, int pos) {
    int proximity = 0;
    int perfect = -1;
    for (int i = 0; i < net->size; i++) {
        if (net->conexions->edges[i][pos].proximity > proximity) {
            proximity = net->conexions->edges[i][pos].proximity;
            perfect = i;
        }
    }

    if(perfect != -1) {
        printf("Your soulmate is: \n");
        printProfile(net->profiles[perfect]);
    } else 
        printf("You are destined to be alone\n");
    
    return;
}

void changeTreshold(Net* net) {
    int treshold;
    printf("What's the new tresh hold?\n");
    scanf("%d", &treshold);
    net->treshold = treshold;
}

void getDistance(Net* net, int pos, int pos2) {
    bfs(net->conexions, pos);
    int dist = net->conexions->distance[pos][pos2];
    
    if(dist == -1) printf("You're not connected at all\n");
    else printf("The distance between %s and %s is: %d", net->profiles[pos].name, net->profiles[pos2].name, dist);
    
    return;
}

void getAllDistances(Net* net) {
    floydWarshall(net->conexions);
    
    for(int i = 0; i < net->size; i++) printf("\t%s", net->profiles[i].name);
    printf("\n");

    for (int i = 0; i < net->size; i++) {
        printf("%s\t", net->profiles[i].name);

        for (int j = 0; j < net->size; j++) {
            if(net->conexions->distance[i][j] == oo) printf("oo\t");
            else printf("%d\t", net->conexions->distance[i][j]);
        }
        printf("\n");
    }
}

void getPrevious(Net* net, int pos, int pos2) {
    bfs(net->conexions, pos2);
    int currId = pos;
    Profile path[maxSize];

    while (net->conexions->prev[currId] != -1) {
        if(currId == pos) printf("\nO caminho para o crush é:");
        currId = net->conexions->prev[currId];
        printf("\n");
        printProfile(net->profiles[currId]);
    }

    if(currId == pos) {
        printf("\nNão dá pra chegar chegando. Fala com um dos amigxs delx\n");
        printFriends(net, pos2);
    }

    return;
}

void printFriends(Net* net, int pos) {
    for (int i = 0; i < net->size; i++) {
        if (net->conexions->edges[pos][i].relation == friends) {
            printf("\n");
            printProfile(net->profiles[i]);
            printf("\n");
        }
    }
}