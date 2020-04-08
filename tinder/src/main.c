// todo:
//      traduzir e colocar memes
//      armazenar dados(matriz de adjacencia)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "adj_matrix.h"
#include "csv.h"

void printMenu() {
    printf("\n-----------------------------\n");
    printf("What do you want to do?\n");
    printf("1 - Insert new profile\n");
    printf("2 - See all profiles\n");
    printf("3 - See someone's profile\n");
    printf("4 - Send an invitation\n");
    printf("5 - See your invitations\n");
    printf("6 - Get some suggestions\n");
    printf("7 - Dected who should not be your friend\n");
    printf("8 - Get perfect Match\n");
    printf("9 - See how far you are from someone\n");
    printf("10 - See everyone's distance\n");
    printf("11 - How to get close to your crush\n");
    printf("12 - Stop people from ever meeting\n");
    printf("13 - See advanced options\n");
    printf("0 - Exit\n");
    printf("-----------------------------\n\n");
    return;
}

void printAdvancedOptions() {
    printf("\n-----------------------------\n");
    printf("1 - See adjacency matrix (proximity|areFriends)\n");
    printf("2 - Show Treshold\n");
    printf("3 - Change Treshold\n");
    printf("-----------------------------\n\n");
    return;
}

void advancedOptions(Net* net) {
    printAdvancedOptions();

    int op = 0;
    scanf("%d", &op);

    if(op == 1) {
        printNames(net->profiles, net->size);
        printMatrix(net->conexions, 0);
    } else if(op == 2) {
        printf("The Tresh Hold is: %d\n", net->treshold);
    } else if(op == 3) {
        changeTreshold(net);
    }

    return;
}

int main() {
    system("clear");
    printf("__          __  _                            \n");
    printf("\\ \\        / / | |                         \n");
    printf(" \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___ \n");
    printf("  \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ \n");
    printf("   \\  /\\  /  __/ | (_| (_) | | | | | |  __/\n");
    printf("    \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \n");
    printf("\n\n");
    printf(" _           _____ _           _ _                 _   _               \n");
    printf("| |         / ____| |         | | |               | \\ | |              \n");
    printf("| |_ ___   | (___ | |__   __ _| | | _____      __ |  \\| | _____      __\n");
    printf("| __/ _ \\   \\___ \\| '_ \\ / _` | | |/ _ \\ \\ /\\ / / | . ` |/ _ \\ \\ /\\ / /\n");
    printf("| || (_) |  ____) | | | | (_| | | | (_) \\ V  V /  | |\\  | (_) \\ V  V / \n");
    printf(" \\__\\___/  |_____/|_| |_|\\__,_|_|_|\\___/ \\_/\\_/   |_| \\_|\\___/ \\_/\\_/  \n\n");

    Net* net = initNet();
    int pos = -1;
    int pos2 = -1;
    int op = 1;
    int error = 0;
    
    do {
        printMenu();
        scanf("%d", &op);
        
        if (op == 1) {
            Profile profile = createProfile();
            insertProfile(net, profile);

        } else if (op == 2) {
            printAllProfiles(net->profiles, net->size);
            
        } else if (op == 3) {
            if(getProfile(net, &pos, 2) == false) continue;
            printProfile(net->profiles[pos]);

        } else if (op == 4) {
            if(getProfile(net, &pos, 1) == false) continue;
            if(getProfile(net, &pos2, 2) == false) continue;
            sendInvitation(net, pos, pos2);

        } else if (op == 5) {
            if(getProfile(net, &pos, 1) == false) continue;
            seeInvitations(net, pos);

        } else if (op == 6) {
            if(getProfile(net, &pos, 1) == false) continue;
            suggestProfile(net, pos);

        } else if (op == 7) {
            if(getProfile(net, &pos, 1) == false) continue;
            fakeFriends(net, pos);

        } else if (op == 8) {
            if(getProfile(net, &pos, 1) == false) continue;
            perfectMatch(net, pos);

        } else if (op == 9) {
            if(getProfile(net, &pos, 1) == false) continue;
            if(getProfile(net, &pos2, 2) == false) continue;
            getDistance(net, pos, pos2);
            
        } else if (op == 10) {
            getAllDistances(net);

        } else if (op == 11) {
            if(getProfile(net, &pos, 1) == false) continue;
            if(getProfile(net, &pos2, 2) == false) continue;
            getPrevious(net, pos, pos2);

        } else if (op == 12) {
            if(getProfile(net, &pos, 1) == false) continue;
            if(getProfile(net, &pos2, 2) == false) continue;
            minCut(net, pos, pos2);

        } else if (op == 13) {
            advancedOptions(net);

        } else if (op != 0) {
            printf("Invalid option\n");

        }

    } while (op != 0);

    insertNetworkCSV(net);
    writeCSV(net->csv, csv_pathway);
    convertToFile(net->conexions, matrix_pathway);

    DestroyCSV(net->csv);
    destroyGraphMatrix(net->conexions, &error);
    if (net != NULL) free(net);

    return 0;
}