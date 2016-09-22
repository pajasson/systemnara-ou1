#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct user{
    long uid;
    char* userName; //free(namn->userName)
}user;

void fillUsers(FILE* read, list* l);

int main(int argc, char *argv[]) {

    FILE* read;

    read = fopen(argv[1], "r");

    list* listan = new_list();
    fillUsers(read, listan);

    element* out = inspect(listan, 1);
    printf("\nUsername: %s", ((user*)out)->userName);
    printf("\nUID: %ld", ((user*)out)->uid);
    printf("\n%d", size(listan));

    return 0;
}

void fillUsers(FILE* read, list* l){

    char rows [1023];
    char* endNr;
    int startNr;
    long nrTemp;
    int i = 0;
    int lineCount = 0;
    int divideCount = 0;
    int fieldCount = 0;
    bool addItem;



    while(fgets(rows, 1023, read) != NULL){
        i = 0;
        divideCount = 0;
        fieldCount = 0;
        addItem = true;
        lineCount++;
        if (rows[0] == '\n'){
            fprintf(stderr, "Line %d: Encountered a <BLANKLINE>\n", lineCount);
            addItem = false;
        }
        while(rows[i] != '\n' && addItem) {
            if(rows[i] == ':'){
                divideCount++;
            }
            i++;
        }
        if(divideCount != 6 && addItem){
            fprintf(stderr, "Line %d: Invalid format: %s\n", lineCount, rows);
            addItem = false;
        }
        i = 0;
        //********username********
        printf("\n\nusername: ");
        while(rows[i] != ':' && addItem){
            printf("%c", rows[i]);
            i++;
        }
        user *namn = malloc(sizeof(user));
        rows[i] = 0;
        if (i >= 1 && i <= 31 && addItem) {
            namn->userName = strdup(rows);
        } else if(addItem){
            fprintf(stderr, "Line %d: Username \"%s\" has invalid length. Expected to be 1-32 characters.\n", lineCount, rows);
            addItem = false;
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
            printf("%c", rows[i]);
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
        //om uid är positivt
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if((rows + startNr)!= endNr){
            if (nrTemp >= 0) {
                namn->uid = nrTemp;
            }else{
                fprintf(stderr, "Line %d: Uid must be positive\n", lineCount);
                addItem = false;
            }
        }else{
            fprintf(stderr, "Line %d: Uid must be a number, got %s\n", lineCount, rows + startNr);
            addItem = false;
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
        endNr = &rows[i];
        //om GID är positivt
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if (nrTemp >= 0 && addItem) {
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
            fieldCount++;
        }
        if (fieldCount < 1) {
            fprintf(stderr, "Line %d: Directory field can not be empty\n", lineCount);
            addItem = false;
        }
        rows[i] = 0;
        i++;

        //********shell*******
        fieldCount = 0;
        printf("\nshell : ");
        while (rows[i] != NULL){
            printf("%c", rows[i]);
            i++;
            fieldCount++;
        }
        if (fieldCount < 2) {
            fprintf(stderr, "Line %d: Shell field can not be empty\n", lineCount);
            addItem = false;
        }
        memset(&rows[0], NULL, sizeof(rows));
        if(addItem){
            insert(l, namn);
        }else{
            free(namn);
        }
    }
}