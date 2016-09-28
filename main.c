#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct user{
    long uid;
    char* userName;
}user;

void fillUsers(FILE* read, list* l);
void sortListUid(list* l);

int main(int argc, char *argv[]) {

    FILE* read;
    if(argc != 2){
        printf("kukerror");
    }
    read = fopen(argv[1], "r");

    list* listan = new_list();
    fillUsers(read, listan);

    sortListUid(listan);
    int i = 1;
    while(i <= size(listan)){
        printf("%ld:%s\n", ((user*)(inspect(listan ,i)))->uid, ((user*)(inspect(listan ,i)))->userName);
        i++;
    }
    i = 1;
    while(i <= size(listan)){
        free(((user*)(inspect(listan ,i)))->userName);
        i++;
    }
    clearList(listan);
    free(listan);
    fclose(read);
    return 0;
}

void fillUsers(FILE* read, list* l){

    char rows [1023];
    char* endNr = NULL;
    int startNr = 0;
    long nrTemp = 0;
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
            fprintf(stderr, "Line %d: Invalid format: %s", lineCount, rows);
            addItem = false;
        }
        i = 0;
        /********username********/
        while(rows[i] != ':' && addItem){
            i++;
        }
        user *namn = calloc(1, sizeof(user));
        rows[i] = 0;
        if (i >= 1 && i <= 31 && addItem) {
            namn->userName = strdup(rows);
        } else if(addItem){
            fprintf(stderr, "Line %d: Username \"%s\" has invalid length. Expected to be 1-32 characters.\n", lineCount, rows);
            addItem = false;
        }
        i++;
        /*********password********/
        while (rows[i] != ':' && addItem) {
            i++;
        }
        rows[i] = 0;
        i++;
        /*******uid*********/
        startNr = i;
        while (rows[i] != ':' && addItem) {
            i++;
            fieldCount++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if(fieldCount > 0 && addItem) {

            if (nrTemp < 0 && addItem) {
                fprintf(stderr, "Line %d: Uid must be a positive integer.\n", lineCount);
            } else if (*endNr != 0 && addItem) {
                fprintf(stderr, "Line %d: Uid must be a number, got \"%s\".\n", lineCount, rows + startNr);
            } else {
                namn->uid = nrTemp;
            }
        }else if(addItem){
            fprintf(stderr, "Line %d: UID field can not be empty.\n", lineCount);
            addItem = false;
        }
        /******GID********/
        fieldCount = 0;
        startNr = i;
        while (rows[i] != ':' && addItem) {
            i++;
            fieldCount++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if(fieldCount > 0 && addItem){

            if(nrTemp < 0 && addItem){
                fprintf(stderr, "Line %d: Gid must be a positive integer.\n", lineCount);
            }else if ( *endNr != 0 && addItem) {
                fprintf(stderr, "Line %d: Gid must be a number, got \"%s\".\n", lineCount, rows + startNr);
            }
        }else if(addItem){
            fprintf(stderr, "Line %d: GID field can not be empty.\n", lineCount);
            addItem = false;
        }
        fieldCount = 0;
        /********GECOS******/
        while (rows[i] != ':' && addItem) {
            i++;
        }
        rows[i] = 0;
        i++;
        /********directory*******/
        while (rows[i] != ':' && addItem) {
            i++;
            fieldCount++;
        }
        if (fieldCount < 1 && addItem) {
            fprintf(stderr, "Line %d: Directory field can not be empty.\n", lineCount);
            addItem = false;
        }
        rows[i] = 0;
        i++;
        /********shell*******/
        fieldCount = 0;
        while (rows[i] != '\0' && addItem){
            i++;
            fieldCount++;
        }
        if (fieldCount < 2 && addItem) {
            fprintf(stderr, "Line %d: Shell field can not be empty.\n", lineCount);
            addItem = false;
        }
        if(addItem){
            insert(l, (element*)namn);
        }else{
            free(namn->userName);
            free(namn);
        }

    }
}

void sortListUid(list* l){
    int j = 0;
    for (int i = 1 ; i <= size(l); i++) {
        j = i;
        while ( j > 1 && ((user*)(inspect(l ,j)))->uid < ((user*)(inspect(l, j-1)))->uid) {
            swapElement(l,j,j-1);
            j--;
        }
    }
}