#ifndef PROFILE_H
#define PROFILE_H

#define nameWeight 1
#define ageWeight 3
#define cityWeight 5
#define movieWeight 6
#define foodWeight 3
#define paperWeight 8
#define algorithmWeight 7
#define avengerWeight 4
#define bestWeight 10

typedef struct _profile {
    char name[300];
    int age;
    char city[300];
    char movie[300];
    char food[300];
    char paper[300];
    char algorithm[300];
    char avenger[300];
    char best[300];
} Profile;

Profile createProfile();
Profile new_Profile(char** atributes);
void printNames(Profile* profiles, int size);
void printProfile(Profile profile);
void printAllProfiles(Profile* profiles, int size);
int searchProfile(Profile* profile, char* name, int size);
int getProximity(Profile this, Profile that);

#endif