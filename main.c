#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct user{
    long uid;
    char* userName; //free(namn->userName)
}user;

void fillUsers(FILE* read, list* l);
void sortListUid(list* l);

int main(int argc, char *argv[]) {

    FILE* read;

    read = fopen(argv[1], "r");

    list* listan = new_list();
    fillUsers(read, listan);

    sortListUid(listan);
    int i = 1;
    while(i < size(listan)){
        printf("%ld:%s\n", ((user*)(inspect(listan ,i)))->uid, ((user*)(inspect(listan ,i)))->userName);
        i++;
    }
    while(i < size(listan)){
        free(((user*)(inspect(listan ,i)))->userName);
        free(inspect(listan ,i));
        i++;
    }
    free(listan);
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
        //check for empty lines
        if (rows[0] == '\n'){
            fprintf(stderr, "Line %d: Encountered a <BLANKLINE>\n", lineCount);
            addItem = false;
        }
        //check if the line is in the correct format with 6 ':'
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
        while(rows[i] != ':' && addItem){
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
        do {
            i++;
        }while (rows[i] != ':');
        rows[i] = 0;
        i++;
        startNr = i;
        //*******uid*********
        while (rows[i] != ':') {
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
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
        while (rows[i] != ':') {
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
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
        //********GECOS******
        while (rows[i] != ':') {
            rows[i] = rows[i];
            i++;
        }
        rows[i] = 0;
        i++;
        //********directory*******
        while (rows[i] != ':') {
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
        while (rows[i] != '\0'){
            i++;
            fieldCount++;
        }
        if (fieldCount < 2) {
            fprintf(stderr, "Line %d: Shell field can not be empty\n", lineCount);
            addItem = false;
        }
        memset(&rows[0], '\0', sizeof(rows));
        if(addItem){
            insert(l, (element*)namn);
        }else{
            free(namn);
        }
    }
}

void sortListUid(list* l){
    int i;
    int j;
    for (i = 1 ; i <= size(l) - 1; i++) {
        j = i;

        while ( j > 0 && ((user*)(inspect(l ,j)))->uid < ((user*)(inspect(l, j-1)))->uid) {
            swapElement(l,j,j-1);

            j--;
        }
    }
}