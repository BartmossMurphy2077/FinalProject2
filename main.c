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

    printf("==================================================\n");
    printf("Record is being added to RAM\n");

    printf("**************************************************\n");
    printf("checking if anything is after five days\n");
    filterByTimeGreaterThan(&records, &size, 5.0);

    printf("**************************************************\n");
    printf("checking if anything is before five days\n");
    filterByTimeLesserThan(&records, &size, 5.0);

    printf("**************************************************\n");
    printf("checking if anything is overdue\n");
    filterByTimeOverdue(&records, &size);

    RecordStructure test;
    strcpy(test.date, "date");
    strcpy(test.description, "00");
    strcpy(test.category, "category1");
    test.priority = 0;
    strcpy(test.status, "00");

    printf("==================================================\n");
    printf("Record is being added to RAM\n");
    addRecordToRam(&records, &size, test);
    readWholeRam(records, &size);

    printf("==================================================\n");
    printf("Category 1 is being filtered\n");
    filterByCategory(&records, &size, "category1");

    printf("==================================================\n");
    printf("Priority 1 is being filtered\n");
    filterByPriority(&records, &size, 1);

    printf("==================================================\n");
    printf("status status4 is being filtered\n");
    filterByStatus(&records, &size, "status4");


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

