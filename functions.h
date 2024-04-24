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
void addRecord(char fileName[100], RecordStructure structure);
void deleteRecord(char fileName[100], int LineNo);
char* ReturnComponent(char fileName[100], int row, int column);
void ChangeComponent(char fileName[100], char changedComponent[100], int row, int column);
int countRows(char fileName[100]);
RecordStructure *createDyanmicArray(char filename[100]);
void freeDynamicArray(RecordStructure *array);
void addRecordToRam(RecordStructure **array, int *size, RecordStructure newItem);
void readWholeRam(RecordStructure *array, int *size);
#endif //FINALPROJECT2_FUNCTIONS_H
