#include <stdio.h>
#include <time.h>

#include "functions.h"

char fileName[100] = "C:\\Users\\hugok\\CLionProjects\\FinalProject2\\info.csv";


int main() {
    printf("Hello, World!\n");

    ReadWholeFIle(fileName);
    deleteRecord(fileName, 0);

    printf("\n");
    ReadWholeFIle(fileName);

    return 0;
}

