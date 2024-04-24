#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

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
// date, description, category, priority, status
void addRecord(char fileName[100], char date[100], char description[100], char category[100], char priority[100], char status[100]){
    FILE *file = fopen(fileName, "a");
    if(file == NULL){
        printf("Error opening file");
        exit(-1);
    } else {
        printf("File opened succesfully for appending\n");
    }

    fprintf(file, "\n%s,%s,%s,%s,%s", date, description, category, priority, status);
    fclose(file);
}
void deleteRecord(char fileName[100], int LineNo){
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
        int current_line = 1;

        // Process data lines
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            current_line++;
            if (current_line != LineNo) {
                fputs(buffer, temp);
            }
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
char* ReturnComponent(char fileName[100], int row, int column){
    FILE *file = fopen(fileName, "r");

    if (file == NULL) {
        printf("Error opening file");
        exit(-1);
    } else {
        printf("File opened successfully for reading\n");

        char *data;
        char buffer[1000];

        //skips to the target row
        for(int i = 0; i < row; i++){
            fgets(buffer, sizeof(buffer), file);
        }
        printf("The target row is: %s\n", buffer);

        if(column == 1){
            data = strtok(buffer, ",");
            printf("The first component is: %s\n", data);
        } else{
            data = strtok(buffer, ",");
            printf("The first component is: %s\n", data);

            for(int i = 0; i < column - 1; i++){
                data = strtok(NULL, ",");
            }
        }

        fclose(file);
        printf("The final output is: %s\n", data);

        return data;
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
int findRow(char fileName[100], char website_name[100]){
    int row_number = 0;
    int aux_var = 0; //variable to track if the files is empty
    char text_line[500], aux_web_name[100], *token;

    strcpy(aux_web_name, website_name);
    strupr(aux_web_name);

    FILE *file = fopen(fileName, "r");

    if(file == NULL){
        printf("Could not open file for reading \n");
        return -1;

    }else{
        while(!feof(file)){
            aux_var=1;
            fgets(text_line, sizeof(text_line), file);
            token = strtok(text_line,",");
            /*printf("%s", token);
            getchar();*/
            row_number = row_number + 1;

            token = strupr(token);

            if(!strcmp(aux_web_name, token)){
                break;
            }
            if(feof(file)){
                row_number = 0;
            }
        }
        if(aux_var==0){
            row_number = 0;
        }
        fclose(file);
        return row_number;
    }
}
