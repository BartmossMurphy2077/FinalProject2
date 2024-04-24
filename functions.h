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
#endif //FINALPROJECT2_FUNCTIONS_H
