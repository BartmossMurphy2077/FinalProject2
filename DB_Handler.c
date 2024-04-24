#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "functions.h"

void ReadWholeFIle(char fileName[100]){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        exit(-1);
    } else {
        printf("File opened succesfully for reading.\n");
    }

    char buffer[1000];

    while(fgets(buffer, sizeof(buffer), file)){
        printf("%s\n", buffer);
    }

    fclose(file);

}

RecordStructure *createDyanmicArray(char filename[100]){

    int size = countRows(filename);


    RecordStructure *array = (RecordStructure *)malloc(size * sizeof(RecordStructure));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(filename, "r");
    if(file == NULL){
        exit(-1);
    } else {
        printf("File opened succesfully for reading.\n");
    }

    char buffer[1000];
    int i = 0;
    while(fgets(buffer, sizeof(buffer), file)){
        char *token = strtok(buffer, ",");
        strcpy(array[i].date, token);

        token = strtok(NULL, ",");
        strcpy(array[i].description, token);

        token = strtok(NULL, ",");
        strcpy(array[i].category, token);

        token = strtok(NULL, ",");
        array[i].priority = atoi(token);

        token = strtok(NULL, ",");
        strcpy(array[i].status, token);

        i++;
    }

    return array;
}

void freeDynamicArray(RecordStructure *array) {
    free(array);
}

void addRecordToRam(RecordStructure **array, int *size, RecordStructure newItem){

    //Realocating memory
    *array = (RecordStructure *) realloc(*array, (*size + 1) * sizeof(RecordStructure ));
    if(*array == NULL){
        printf("Memory reallocation failed\n");
        exit(-1);
    }

    //putting the new item into the array
    (*array)[*size] = newItem;

    //udpate the size

    (*size)++;
}

void deleteRecordInRam(RecordStructure **array, int *size, char word[100]){
    int found = 0;
    for(int i = 0; i< *size; i++){
        if (strstr((*array)[i].description, word) != NULL ||
            strstr((*array)[i].category, word) != NULL ||
            strstr((*array)[i].status, word) != NULL) {
            found = 1;
            // Shift elements after the deleted item to the left
            for (int j = i; j < *size - 1; j++) {
                (*array)[j] = (*array)[j + 1];
            }
            break;
        }
    }
    if (found) {
        // Adjust the size of the dynamic array
        *size -= 1;
        // Reallocate memory to shrink the dynamic array
        *array = (RecordStructure *)realloc(*array, (*size) * sizeof(RecordStructure));
        if (*array == NULL) {
            fprintf(stderr, "Memory reallocation failed\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("No record containing '%s' found\n", word);
    }
}

void readWholeRam(RecordStructure *array, int *size){
    for(int i = 0; i < *size; i++){
        printf("Record %d:\n", i + 1);
        printf("Date: %s\n", array[i].date);
        printf("Description: %s\n", array[i].description);
        printf("Category: %s\n", array[i].category);
        printf("Priority: %d\n", array[i].priority);
        printf("Status: %s\n", array[i].status);
        printf("\n");
    }
}
void ChangeComponent(char fileName[100], char changedComponent[100], int row, int column){
    FILE *temp;
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error opening file");
        exit(-1);
    } else {
        printf("File opened successfully for reading\n");

        temp = tmpfile();
        if (temp == NULL) {
            printf("Error creating temporary file");
            exit(-1);
        } else {
            printf("Temporary file created successfully\n");
        }

        char buffer[1000];
        int currentRow = 0;

        while(fgets(buffer, sizeof(buffer), file)){
            char *data = strtok(buffer, ",");
            int currentColumn = 0;

            if (data == NULL) {
                continue;
            }

            // Check if the line is empty
            if (strcmp(data, "\n") == 0) {
                fprintf(temp, "\n");
                currentRow++;
                continue;
            }

            while(data != NULL){
                if(currentRow == row - 1 && currentColumn == column - 1){
                    if(currentColumn == 4){
                        fprintf(temp, "%s\n", changedComponent);
                        printf("The component has been changed\n");
                    } else {
                        fprintf(temp, "%s,", changedComponent);
                        printf("The component has been changed\n");
                    }
                } else if(currentColumn == 4){
                    fprintf(temp, "%s", data);
                } else {
                    fprintf(temp, "%s,", data);
                }

                data = strtok(NULL, ",");
                currentColumn++;
            }
            //fprintf(temp, "\n");
            currentRow++;
        }

        fclose(file);
        rewind(temp);

        file = fopen(fileName, "w");
        if (file == NULL) {
            printf("Error opening file for writing");
            exit(-1);
        } else {
            printf("File opened successfully for writing\n");
        }

        while (fgets(buffer, sizeof(buffer), temp) != NULL) {
            fputs(buffer, file);
        }

        fclose(file);
        fclose(temp);
    }
}
int countRows(char fileName[100]){
    FILE *file = fopen(fileName, "r");
    if(file == NULL){
        printf("Error opening file for reading");
        exit(-1);
    } else {
        char buffer[1000];
        int current_line = 0;

        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            current_line++;
        }
        fclose(file);
        return current_line;
    }
}
