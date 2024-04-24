#include <stdio.h>
#include <time.h>
#include <string.h>

#include "functions.h"

char fileName[100] = "C:\\Users\\hugok\\CLionProjects\\FinalProject2\\info.csv";


int main() {
    printf("Hello, World!\n");

    ReadWholeFIle(fileName);

    printf("\n");
    ReadWholeFIle(fileName);

    // Create dynamic array of RecordStructure
    RecordStructure *records = createDyanmicArray(fileName);

    // Get the number of records
    int size = countRows(fileName);

    // Iterate through records and print details
//    for (int i = 0; i < size; i++) {
//        printf("Record %d:\n", i + 1);
//        printf("Date: %s\n", records[i].date);
//        printf("Description: %s\n", records[i].description);
//        printf("Category: %s\n", records[i].category);
//        printf("Priority: %d\n", records[i].priority);
//        printf("Status: %s\n", records[i].status);
//        printf("\n");
//    }

    readWholeRam(records, &size);

    RecordStructure test;
    strcpy(test.date, "000");
    strcpy(test.description, "00");
    strcpy(test.category, "000");
    test.priority = 0;
    strcpy(test.status, "00");

    addRecordToRam(&records, &size, test);

    readWholeRam(records, &size);

    // Free the dynamically allocated memory
    freeDynamicArray(records);

    return 0;
}

