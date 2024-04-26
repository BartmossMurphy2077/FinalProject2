#ifndef FINALPROJECT2_FUNCTIONS_H
#define FINALPROJECT2_FUNCTIONS_H

//structure
typedef struct{
    char date[100];
    char description[100];
    char category[100];
    int priority;
    char status[100];
}RecordStructure;

//DB_Handler.c
void ReadWholeFIle(char fileName[100]);
int countRows(char fileName[100]);
RecordStructure *createDyanmicArray(char filename[100]);
void freeDynamicArray(RecordStructure *array);
void addRecordToRam(RecordStructure **array, int *size, RecordStructure newItem);
void readWholeRam(RecordStructure *array, int *size);
void deleteRecordInRam(RecordStructure **array, int *size, char word[100]);
void saveRamToCsv(char fileName[100], RecordStructure **array, int *size);
void changeDate(RecordStructure **array, int columnNo, char newDate[100]);
void changeDescription(RecordStructure **array, int columnNo, char newDescription[100]);
void changeCategory(RecordStructure **array, int columnNo, char newCategory[100]);
void changePriority(RecordStructure **array, int columnNo, int newPriority);
void changeStatus(RecordStructure **array, int columnNo, char newStatus[100]);
void filterByCategory(RecordStructure **array, int *size, char category[100]);
void filterByPriority(RecordStructure **array, int *size, int priority);
void filterByStatus(RecordStructure **array, int *size, char status[100]);

double presentFutureDifference(char futureDate[100]);
#endif //FINALPROJECT2_FUNCTIONS_H
