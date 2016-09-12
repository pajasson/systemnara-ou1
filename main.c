#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct user{
    unsigned int uid;
    char* userName; //free(namn->userName)
}user;

void fillUsers(FILE* read, list* l);

int main(int argc, char *argv[]) {

    FILE* read;

    read = fopen(argv[1], "r");

    list* listan = new_list();
    fillUsers(read, listan);

    element* out = inspect(listan, 3);
    printf("\nUsername: %s", ((user*)out)->userName);
    printf("\nUID: %d", ((user*)out)->uid);
    printf("\n%d", size(listan));

    return 0;
}

void fillUsers(FILE* read, list* l){

    char rows [1023];
    char* endNr;
    int startNr;
    unsigned int nrTemp;
    int i;
    //bool addItem = true;



    while(fgets(rows, 1023, read) != NULL){

        i = 0;
        //********username********
        printf("\n\nusername: ");
        while(rows[i] != ':'){
            printf("%c", rows[i]);
            i++;
        }
        user *namn = malloc(sizeof(user));
        rows[i] = 0;
        if (i >= 1 && i <= 32) {
            namn->userName = strdup(rows);
        } else {
            //nått stdout error grejs (ingen insert)
        }
        i++;
        //*********password********
        printf("\npassword: ");
        do {
            printf("%c ", rows[i]);
            i++;
        }while (rows[i] != ':');
        rows[i] = 0;
        i++;
        startNr = i;
        //*******uid*********
        printf("\nuid: ");
        while (rows[i] != ':') {
            if(rows[i] < '0' || rows[i] > '9'){
                //std out error grejs ingen insert(ska va siffra)
            }
            printf("%c", rows[i]);
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = rows[i];
        //om uid är positivt
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if (nrTemp >= 0) {
            namn->uid = nrTemp;
        } else {
            //nått stdout error grejs (ingen insert)
        }

        //******GID********

        startNr = i;
        printf("\ngid: ");
        while (rows[i] != ':') {
            if(rows[i] < '0' || rows[i] > '9'){
                //std out error grejs ingen insert(ska va siffra)
            }
            printf("%c", rows[i]);
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = rows[i];
        //om GID är positivt
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if (nrTemp >= 0) {
            namn->uid = strtol(rows + startNr, &endNr, 10);
        } else {
            //nått stdout error grejs (ingen insert)
        }
        //********GECOS******
        printf("\nGECOS : ");
        while (rows[i] != ':') {
            printf("%c", rows[i]);
            rows[i] = rows[i];
            i++;
        }
        rows[i] = 0;
        i++;
        //********directory*******

        printf("\ndirectory : ");
        while (rows[i] != ':') {
            printf("%c", rows[i]);
            rows[i] = rows[i];
            i++;
        }
        if (i >= 1) {

        } else {
            //nått stdout error grejs (ingen insert)
        }
        rows[i] = 0;
        i++;

        //********shell*******
        printf("\nshell : ");
        while (rows[i] != NULL){
            printf("%c", rows[i]);
            i++;
        }
        if (i >= 1) {

        } else {
            //nått stdout error grejs (ingen insert)
        }
        memset(&rows[0], NULL, sizeof(rows));
        insert(l, namn);
    }
}