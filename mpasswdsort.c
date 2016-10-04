#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include "string.h"

#define MAXLINELENGTH 1023

typedef struct user{
    long uid;
    char* userName;
}user;

bool fillUsers(FILE* read, list* l);
void sortListUid(list* l);
/*
 * The main function for the passwordsort program. it reads from the file specified in the argument
 * and stores the element in a list which is then sorted with an insertionsort based on the elements
 * UID number
 */
int main(int argc, char *argv[]) {

    FILE* read;
    bool result;
    if (argc == 1){
        read = stdin;
    }else {
        read = fopen(argv[1], "r");
    }
    if (!read){
        perror(argv[1]);
        exit(EXIT_FAILURE);
    }

    list* listan = new_list();
    result = fillUsers(read, listan);

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

    if(!result){
        exit(EXIT_FAILURE);
    }
    exit(0);
}
/*
 * This function reads from the input-file and checks each line for userinformation.
 * The username and uid-number are saved in "users" and added to the list.
 * if any errors occurs the function prints a message to stderr and returns
 * false after its done.
 */
bool fillUsers(FILE* read, list* l){

    char rows [MAXLINELENGTH];
    char* endNr = NULL;
    int startNr = 0;
    long nrTemp = 0;
    int i = 0;
    int lineCount = 0;
    int divideCount = 0;
    int fieldCount = 0;
    bool addItem;
    bool returnValue = true;

    while(fgets(rows, MAXLINELENGTH, read) != NULL){

        i = 0;
        divideCount = 0;
        fieldCount = 0;
        addItem = true;
        lineCount++;
        //check if the line is empty
        if (rows[0] == '\n'){
            fprintf(stderr, "Line %d: Encountered a <BLANKLINE>\n", lineCount);
            addItem = false;
            returnValue = false;
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
            returnValue = false;
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
            returnValue = false;
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
                addItem = false;
            } else if (*endNr != 0 && addItem) {
                fprintf(stderr, "Line %d: Uid must be a number, got \"%s\".\n", lineCount, rows + startNr);
                addItem = false;
            } else {
                namn->uid = nrTemp;
            }
        }else if(addItem){
            fprintf(stderr, "Line %d: UID field can not be empty.\n", lineCount);
            addItem = false;
            returnValue = false;
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
                addItem = false;
            }else if ( *endNr != 0 && addItem) {
                fprintf(stderr, "Line %d: Gid must be a number, got \"%s\".\n", lineCount, rows + startNr);
                addItem = false;
            }
        }else if(addItem){
            fprintf(stderr, "Line %d: GID field can not be empty.\n", lineCount);
            addItem = false;
            returnValue = false;
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
            returnValue = false;
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
            returnValue = false;
        }
        if(addItem){
            insert(l, (element*)namn);
        }else{
            free(namn->userName);
            free(namn);
        }

    }
    return returnValue;
}
/*
 * This function performs an insertionsort on the list by UID-nr in ascending order
 */
/*void sortListUid(list* l){
    int j = 0;
    int i;
    for (i = 1 ; i <= size(l); i++) {
        j = i;
        while (j > 1 && ((user*)(inspect(l ,j)))->uid < ((user*)(inspect(l, j-1)))->uid) {
            swapElement(l,j,j-1);
            j--;
        }
    }
}*/
void sortListUid(list* l){

    int i,j,k,num;
    num = size(l);

    for(i = num / 2; i > 0; i = i/2){

        for(j = i; j < num; j++){

            for(k = j-i + 1; k >= 1; k = k-i){

                if(((user*)(inspect(l ,k+i)))->uid >= ((user*)(inspect(l, k)))->uid){

                    break;

                }else{

                    swapElement(l,k,k+i);
                }
            }
        }
    }
}