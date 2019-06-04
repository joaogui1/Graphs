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

    printf("Team: ");
    scanf(" %[^\r\n]", profile.team);

    printf("Favorite color: ");
    scanf(" %[^\r\n]", profile.color);

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
    printf("Favorite Movie: %s\n", profile.movie);
    printf("Team: %s\n", profile.team);
    printf("Favorite Color: %s\n", profile.color);
    
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
    if (!strcmp(this.team, that.team)) ret += teamWeight;
    if (!strcmp(this.color, that.color)) ret += colorWeight;
    if (this.age == that.age) ret += ageWeight;
    
    return ret;
}