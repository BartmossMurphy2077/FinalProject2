#ifndef FINALPROJECT2_FUNCTIONS_H
#define FINALPROJECT2_FUNCTIONS_H

//DB_Handler.c
void ReadWholeFIle(char fileName[100]);
void addRecord(char fileName[100], char date[100], char description[100], char category[100], char priority[100], char status[100]);
void deleteRecord(char fileName[100], int LineNo);
char* ReturnComponent(char fileName[100], int row, int column);
void ChangeComponent(char fileName[100], char changedComponent[100], int row, int column);
int countRows(char fileName[100]);
int findRow(char fileName[100], char website_name[100]);

#endif //FINALPROJECT2_FUNCTIONS_H
