#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
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

//functions for changing components
void changeDate(RecordStructure **array, int columnNo, char newDate[100]){
    strcpy((*array)[columnNo].date, newDate);
}
void changeDescription(RecordStructure **array, int columnNo, char newDescription[100]){
    strcpy((*array)[columnNo].description, newDescription);
}
void changeCategory(RecordStructure **array, int columnNo, char newCategory[100]){
    strcpy((*array)[columnNo].category, newCategory);
}
void changePriority(RecordStructure **array, int columnNo, int newPriority){
    (*array)[columnNo].priority = newPriority;
}
//for change status the new string needs to have a \n on the end for saving purposes
void changeStatus(RecordStructure **array, int columnNo, char newStatus[100]){
    strcpy((*array)[columnNo].status, newStatus);
}

//function that finds how many days from today the thing is due
double presentFutureDifference(char futureDate[100]){
    char copyFutureDate[100];

    strncpy(copyFutureDate, futureDate, sizeof(copyFutureDate)-1);
    copyFutureDate[sizeof(copyFutureDate) - 1] = '\0';

    char *day = strtok(copyFutureDate, "/");
    char *month = strtok(NULL, "/");
    char *year = strtok(NULL, "/");

    int dayValue;
    int monthValue;
    int yearValue;
    double differenceInSeconds;
    double differenceInDays;

    if(day != NULL && month != NULL && year != NULL){
        dayValue = atoi(day);
        monthValue = atoi(month) - 1; //because jan is 0, etc.
        yearValue = atoi(year) - 1900; //cause its since 1900 or something

        printf("Day: %d, Month: %d, Year: %d\n", dayValue, monthValue, yearValue);

        struct tm futureDateStruct = {0};
        time_t currentTime = time(NULL);

        futureDateStruct.tm_year = yearValue;
        futureDateStruct.tm_mon = monthValue;
        futureDateStruct.tm_mday = dayValue;

        time_t futureTime = mktime(&futureDateStruct);

        //a check to see if the date is really in the future (can be used to check things that are overdue)
        if (futureTime == -1) {
            printf("Date not in the future.\n");
            return -1.0;
        }

        //calculating the difference in seconds
        differenceInSeconds = difftime(futureTime, currentTime);

        //turning it into days
        differenceInDays = differenceInSeconds/(24*60*60);

        return differenceInDays;


    } else {
        printf("Invalid date format: %s\n", futureDate);
        return -1.0;
    }

}

//function that uses the presentFutureDifference function to list the things that are due in a certain time interval
void filterByTimeGreaterThan(RecordStructure **array, int *size, double timeInterval){
    int found = 0;
    for(int i = 0; i<*size; i++){
        if(presentFutureDifference((*array)[i].date) >= timeInterval){
            printf("Date: %s\n", (*array)[i].date);
            printf("Description: %s\n", (*array)[i].description);
            printf("Category: %s\n", (*array)[i].category);
            printf("Priority: %d\n", (*array)[i].priority);
            printf("Status: %s\n", (*array)[i].status);
            found++;
        }
    }
    if(found == 0){
        printf("No record which is due after %f days passed found\n", timeInterval);
    }
}

void filterByTimeLesserThan(RecordStructure **array, int *size, double timeInterval){
    int found = 0;
    for(int i = 0; i<*size; i++){
        if(presentFutureDifference((*array)[i].date) <= timeInterval){
            printf("Date: %s\n", (*array)[i].date);
            printf("Description: %s\n", (*array)[i].description);
            printf("Category: %s\n", (*array)[i].category);
            printf("Priority: %d\n", (*array)[i].priority);
            printf("Status: %s\n", (*array)[i].status);
            found++;
        }
    }
    if(found == 0){
        printf("No record which is due within %f days found\n", timeInterval);
    }
}

void filterByTimeOverdue(RecordStructure **array, int *size){
    int found = 0;
    for(int i = 0; i<*size; i++){
        if(presentFutureDifference((*array)[i].date) <= 0){
            printf("Date: %s\n", (*array)[i].date);
            printf("Description: %s\n", (*array)[i].description);
            printf("Category: %s\n", (*array)[i].category);
            printf("Priority: %d\n", (*array)[i].priority);
            printf("Status: %s\n", (*array)[i].status);
            found++;
        }
    }
    if(found == 0){
        printf("No record which is overdue found\n");
    }
}

//categories: Work, Hobby, Home
//should print out all the records with the specified category
void filterByCategory(RecordStructure **array, int *size, char category[100]){
    int found = 0;
    for(int i = 0; i <*size; i++){
        if(strstr((*array)[i].category, category) != NULL){
            printf("Date: %s\n", (*array)[i].date);
            printf("Description: %s\n", (*array)[i].description);
            printf("Category: %s\n", (*array)[i].category);
            printf("Priority: %d\n", (*array)[i].priority);
            printf("Status: %s\n", (*array)[i].status);
            found++;
        }
    }

    if(found == 0){
        printf("No record with specified category was found\n");
    }
}
//Priority levels: 1(Very urgent), 2(urgent), 3(not urgent)
void filterByPriority(RecordStructure **array, int *size, int priority){
    int found = 0;
    for(int i = 0; i<*size; i++){
        if((*array)[i].priority == priority){
            printf("Date: %s\n", (*array)[i].date);
            printf("Description: %s\n", (*array)[i].description);
            printf("Category: %s\n", (*array)[i].category);
            printf("Priority: %d\n", (*array)[i].priority);
            printf("Status: %s\n", (*array)[i].status);
            found++;
        }
    }

    if(found == 0){
        printf("No record with specified priority level was found\n");
    }

}
//Status levels: Completed, In progress, No status
void filterByStatus(RecordStructure **array, int *size, char status[100]){
    int found = 0;
    for(int i = 0; i <*size; i++){
        if(strstr((*array)[i].status, status) != NULL){
            printf("Date: %s\n", (*array)[i].date);
            printf("Description: %s\n", (*array)[i].description);
            printf("Category: %s\n", (*array)[i].category);
            printf("Priority: %d\n", (*array)[i].priority);
            printf("Status: %s\n", (*array)[i].status);
            found++;
        }
    }

    if(found == 0){
        printf("No record with specified status was found\n");
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

void saveRamToCsv(char fileName[100], RecordStructure **array, int *size){
    FILE *temp = tmpfile();
    if(temp == NULL){
        printf("Couldn't create temporary file\n");
        exit(-1);
    }

    for(int i = 0; i < *size-1; i++){
        char String[500];
        snprintf(String, sizeof(String), "%s,%s,%s,%d,%s", (*array)[i].date, (*array)[i].description, (*array)[i].category, (*array)[i].priority, (*array)[i].status);
        printf("\n*********\n");
        printf("%s", String);
        printf("\n*********\n");
        fputs(String, temp);
    }
    char String[500];
    snprintf(String, sizeof(String), "\n%s,%s,%s,%d,%s", (*array)[*size-1].date, (*array)[*size-1].description, (*array)[*size-1].category, (*array)[*size-1].priority, (*array)[*size-1].status);
    printf("\n*********\n");
    printf("%s", String);
    printf("\n*********\n");
    fputs(String, temp);

    //
    rewind(temp);
    printf("=========================================\n");

    char buffer2[1000];
    size_t bytesRead;

    // Read and print each block of data until the end of the file
    while ((bytesRead = fread(buffer2, 1, sizeof(buffer2), temp)) > 0) {
        // Print or process the data as needed
        fwrite(buffer2, 1, bytesRead, stdout);
    }

    // Check for errors or end of file
    if (feof(temp)) {
        printf("End of file reached.\n");
    } else if (ferror(temp)) {
        printf("Error reading file.\n");
    }

    printf("=========================================\n");

    //

    rewind(temp);

    FILE *file = fopen(fileName, "w");
    if(fileName == NULL){
        printf("Couldn't create temporary file\n");
        exit(-1);
    }

    char buffer[500];
    while(fgets(buffer, sizeof(buffer), temp) != NULL){
        fputs(buffer, file);
    }

    fclose(file);
    fclose(temp);
}



//date,description,category,1,status