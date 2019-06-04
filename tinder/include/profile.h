#ifndef PROFILE_H
#define PROFILE_H

#define nameWeight 1
#define cityWeight 2
#define movieWeight 3
#define teamWeight 3
#define colorWeight 2
#define ageWeight 1

typedef struct _profile {
    char name[300];
    int age;
    char city[300];
    char movie[300];
    char team[300];
    char color[300];
} Profile;

Profile createProfile();
void printNames(Profile* profiles, int size);
void printProfile(Profile profile);
void printAllProfiles(Profile* profiles, int size);
int searchProfile(Profile* profile, char* name, int size);
int getProximity(Profile this, Profile that);

#endif