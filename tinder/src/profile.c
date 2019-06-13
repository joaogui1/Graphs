#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "profile.h"

Profile createProfile() {
    Profile profile;

    printf("Insert your data: \n");
    
    printf("Name: ");
    scanf(" %[^\r\n]", profile.name);
    
    printf("Age: ");
    scanf("%d", &profile.age);

    printf("City: ");
    scanf(" %[^\r\n]", profile.city);

    printf("Favorite movie: ");
    scanf(" %[^\r\n]", profile.movie);

    printf("Favorite food: ");
    scanf(" %[^\r\n]", profile.food);

    printf("Favorite paper: ");
    scanf(" %[^\r\n]", profile.paper);

    printf("Favorite graph algorithm: ");
    scanf(" %[^\r\n]", profile.algorithm);

    printf("Favorite Avenger: ");
    scanf(" %[^\r\n]", profile.avenger);

    printf("Favorite soccer team and why São Caetano: ");
    scanf(" %[^\r\n]", profile.best);

    return profile;
}

Profile new_Profile(char** atributes){
    Profile profile;
    strncpy(profile.name, atributes[0], 300);
    profile.age = atoi(atributes[1]);
    strncpy(profile.city, atributes[2], 300);
    strncpy(profile.movie, atributes[3], 300);
    strncpy(profile.food, atributes[4], 300);
    strncpy(profile.paper, atributes[5], 300);
    strncpy(profile.algorithm, atributes[6], 300);
    strncpy(profile.avenger, atributes[7], 300);
    strncpy(profile.best, atributes[8], 300);
    return profile;
}

void printNames(Profile* profiles, int size) {
    for(int i = 0; i < size; i++) {
        printf("%s\t", profiles[i].name);
    }
    printf("\n");
}

void printProfile(Profile profile) {
    printf("Name: %s\n", profile.name);
    printf("Age: %d\n", profile.age);
    printf("City: %s\n", profile.city);
    printf("Favorite movie: %s\n", profile.movie);
    printf("Favorite food: %s\n", profile.food);
    printf("Favorite paper: %s\n", profile.paper);
    printf("Favorite graph algorithm: %s\n", profile.algorithm);
    printf("Favorite Avenger: %s\n", profile.avenger);
    printf("Favorite soccer team: São Caetano\n");

    return;
}

void printAllProfiles(Profile* profiles, int size) {
    for(int i = 0; i < size; i++) {
        printProfile(profiles[i]);
        printf("\n");
    }
    printf("\n");
    return;
}

int searchProfile(Profile* profiles, char* name, int size) {
    for(int i = 0; i < size; i++) {
        if(!strcmp(profiles[i].name, name)) return i;
    }

    return -1;
}

int getProximity(Profile this, Profile that) {
    int ret = 0;

    if (!strcmp(this.name, that.name)) ret += nameWeight;
    if (!strcmp(this.city, that.city)) ret += cityWeight;
    if (!strcmp(this.movie, that.movie)) ret += movieWeight;
    if (!strcmp(this.food, that.food)) ret += foodWeight;
    if (!strcmp(this.paper, that.paper)) ret += paperWeight;
    if (!strcmp(this.algorithm, that.algorithm)) ret += algorithmWeight;
    if (!strcmp(this.avenger, that.avenger)) ret += avengerWeight;
    if (!strcmp(this.best, that.best)) ret += bestWeight;
    if (this.age == that.age) ret += ageWeight;
    
    return ret;
}