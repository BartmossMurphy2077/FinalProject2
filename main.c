#include <stdio.h>
#include <time.h>
#include <string.h>

#include "functions.h"

char fileName[100] = "C:\\Users\\hugok\\CLionProjects\\FinalProject2\\info.csv";


int main() {
    ReadWholeFIle(fileName);

    // Create dynamic array of RecordStructure
    RecordStructure *records = createDyanmicArray(fileName);

    // Get the number of records
    int size = countRows(fileName);

    printf("==================================================\n");
    printf("Reading RAM\n");
    readWholeRam(records, &size);

    RecordStructure test;
    strcpy(test.date, "date");
    strcpy(test.description, "00");
    strcpy(test.category, "000");
    test.priority = 0;
    strcpy(test.status, "00");

    addRecordToRam(&records, &size, test);

    readWholeRam(records, &size);

    deleteRecordInRam(&records, &size, "description3");
    printf("==================================================\n");
    printf("\nNow all description 3 deleted \n");
    readWholeRam(records, &size);

    printf("==================================================\n");
    printf("\n changing 1 columns components \n");
    changeDate(&records, 1, "0/0/0");
    changeDescription(&records, 1, "yolo");
    changeCategory(&records, 1, "bruh");
    changePriority(&records, 1, 69);
    changeStatus(&records, 1, "skibiddy\n");
    readWholeRam(records, &size);




    //csv file before saving
    printf("==================================================\n");
    printf("\nFile is being read \n");
    ReadWholeFIle(fileName);
    printf("\n");
    printf("==================================================\n");
    printf("\nRam being saved to CSV \n");
    saveRamToCsv(fileName, &records, &size);
    printf("==================================================\n");
    printf("\n csv file after saving\n");
    ReadWholeFIle(fileName);

    // Free the dynamically allocated memory
    freeDynamicArray(records);

    return 0;
}

