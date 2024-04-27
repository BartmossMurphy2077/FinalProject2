#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "functions.h"

char fileName[100] = "C:\\Users\\hugok\\CLionProjects\\FinalProject2\\info.csv";

int response = -1;
char strResponse[100] = "";

int main() {
    // Create dynamic array of RecordStructure
    RecordStructure *records = createDyanmicArray(fileName);

    // Get the number of records
    int size = countRows(fileName);



    //The Menu Handling system
    bool displayMenu = true;
    while(displayMenu){
        printf("\n================================================================================================\n");
        printf("Here are the commands: \n0: Save and Close\n1: Add Record\n2: Change Record\n3: Delete Record \n4: Viewing Options\n");

        printf("Please input your response: ");
        scanf("%d", &response);

        switch(response){
            case 0:
                saveRamToCsv(fileName, &records, &size);
                displayMenu = false;
                break;
            case 1:
                printf("\n");

                //initializing the structure
                RecordStructure newRecord;

                //date input
                printf("\nPlease enter a date in the day/month/year format (example: 1/1/2001): ");

                if(scanf("%s", strResponse) != 1){
                    printf("Invalid input\n");
                    strcpy(strResponse, "");
                    break;
                }

                //format check
                int day, month, year;
                if(sscanf(strResponse, "%d/%d/%d", &day, &month, &year) != 3){
                    printf("Input does not match the expected date format");
                    strcpy(strResponse, "");
                    break;
                }

                //validating the range of the days, months and years
                if(day < 1 || day > 31 || month < 1 || month > 12 || year < 0){
                    printf("Invalid date\n");
                    break;
                }
                //adding date
                snprintf(newRecord.date, sizeof(newRecord.date), "%02d/%02d/%04d", day, month, year);


                printf("Date: %s\n", newRecord.date); //test

                //description input
                char Description[100];

                printf("Please enter a description: \n");
                scanf(" %[^\n]s", Description);

                strcpy(newRecord.description, Description);

                //category input
                printf("Please enter one of these Categories:\n1: Work\n 2: Hobby\n3: Home\n4: Other");
                scanf("%d", &response);

                if(response < 1 || response > 4){
                    printf("Invalid input\n");
                    response = -1;
                    break;
                }

                if(response == 1){
                    strcpy(newRecord.category, "Work");
                } else if(response == 2){
                    strcpy(newRecord.category, "Hobby");
                } else if(response == 3){
                    strcpy(newRecord.category, "Home");
                } else {
                    strcpy(newRecord.category, "Other");
                }

                response = -1;

                //priority input
                printf("Please enter a priority level:\n1(Very urgent)\n2(Urgent)\n3(Not urgent)");
                scanf("%d", &response);

                if(response < 1 || response > 3){
                    printf("Invalid input\n");
                    response = -1;
                    break;
                }

                if(response == 1){
                    newRecord.priority = 1;
                } else if(response == 2){
                    newRecord.priority = 2;
                } else {
                    newRecord.priority = 3;
                }

                response = -1;

                //status input
                printf("Please enter one of these Statuses:\n1: Complete\n 2: In Progress\n3: No Status");
                scanf("%d", &response);

                if(response < 1 || response > 3){
                    printf("Invalid input\n");
                    response = -1;
                    break;
                }

                if(response == 1){
                    strcpy(newRecord.status, "Complete");
                } else if(response == 2){
                    strcpy(newRecord.status, "In Progress");
                } else {
                    strcpy(newRecord.status, "No status");
                }
                response = -1;

                //adding the new Record to RAM
                addRecordToRam(&records, &size, newRecord);


                break;
            case 2:

                printf("This is the whole database at the moment: \n");
                printf("=================================================\n");
                readWholeRam(records, &size);
                printf("=================================================\n");

                printf("Which specific Record do you want to edit?\n");
                int columnNO;
                scanf("%d", &columnNO);
                printf("column No: %d\n", columnNO);

                if(columnNO < 0 || columnNO > size){
                    printf("Request out of bounds.\n");
                    response = -1;
                    break;
                }

                printf("What specifically do you want to edit?\n1: date\n2: description\n3: category\n4: priority\n5: status");
                int choice;
                scanf("%d", &choice);
                printf("choice: %d\n", choice);

                if(choice < 0 || choice > 5){
                    printf("Request out of bounds.\n");
                    response = -1;
                    break;
                }

                if(choice == 1){
                    //changing the date
                    char newDate[100];

                    printf("\nPlease enter a date in the day/month/year format (example: 1/1/2001): ");

                    if(scanf("%s", strResponse) != 1){
                        printf("Invalid input\n");
                        strcpy(strResponse, "");
                        break;
                    }

                    //format check
                    int day, month, year;
                    if(sscanf(strResponse, "%d/%d/%d", &day, &month, &year) != 3){
                        printf("Input does not match the expected date format");
                        strcpy(strResponse, "");
                        break;
                    }

                    //validating the range of the days, months and years
                    if(day < 1 || day > 31 || month < 1 || month > 12 || year < 0){
                        printf("Invalid date\n");
                        strcpy(strResponse, "");
                        response = -1;
                        break;
                    }
                    //adding date
                    snprintf(newDate, sizeof(newDate), "%02d/%02d/%04d", day, month, year);
                    changeDate(&records, columnNO - 1, newDate);
                    printf("Date changed successfully to %s at record %d \n", newDate, columnNO);

                    strcpy(strResponse, "");
                    response = -1;

                } else if(choice == 2){
                    //changing the description
                    char newDescription[100];
                    printf("Please enter a new description: \n");
                    scanf(" %[^\n]s", newDescription);
                    changeDescription(&records, columnNO - 1, newDescription);
                    printf("Description succesfully changed at record %d \n", columnNO - 1);

                    response = -1;

                } else if(choice == 3){
                    //changing category
                    printf("Please enter one of these Categories:\n1: Work\n 2: Hobby\n3: Home\n4: Other");
                    scanf("%d", &response);

                    if(response < 1 || response > 4){
                        printf("Invalid input\n");
                        response = -1;
                        break;
                    }

                    if(response == 1){
                        changeCategory(&records, columnNO - 1, "Work");
                    } else if(response == 2){
                        changeCategory(&records, columnNO - 1, "Hobby");
                    } else if(response == 3){
                        changeCategory(&records, columnNO - 1, "Home");
                    } else {
                        changeCategory(&records, columnNO - 1, "Other");
                    }

                    response = -1;


                } else if(choice == 4){
                    //changing priority
                    printf("Please enter a priority level:\n1(Very urgent)\n2(Urgent)\n3(Not urgent)");
                    scanf("%d", &response);

                    if(response < 1 || response > 3){
                        printf("Invalid input\n");
                        response = -1;
                        break;
                    }

                    if(response == 1){
                        changePriority(&records, columnNO - 1, 1);
                    } else if(response == 2){
                        changePriority(&records, columnNO - 1, 2);
                    } else {
                        changePriority(&records, columnNO - 1, 3);
                    }

                    response = -1;

                } else {
                    //changing status
                    printf("Please enter one of these Statuses:\n1: Complete\n 2: In Progress\n3: No Status");
                    scanf("%d", &response);

                    if(response < 1 || response > 3){
                        printf("Invalid input\n");
                        response = -1;
                        break;
                    }

                    if(columnNO == size){
                        if(response == 1){
                            changeStatus(&records, columnNO - 1, "Complete");
                        } else if(response == 2){
                            changeStatus(&records, columnNO - 1, "In Progress");
                        } else {
                            changeStatus(&records, columnNO - 1, "No Status");
                        }
                    } else {
                        if(response == 1){
                            changeStatus(&records, columnNO - 1, "Complete\n");
                        } else if(response == 2){
                            changeStatus(&records, columnNO - 1, "In Progress\n");
                        } else {
                            changeStatus(&records, columnNO - 1, "No Status\n");
                        }
                    }

                    response = -1;
                }

                printf("This is the edited database at the moment: \n");
                printf("=================================================\n");
                readWholeRam(records, &size);
                printf("=================================================\n");

                response = -1;

                break;
            case 3:
                printf("This is the whole database at the moment: \n");
                printf("=================================================\n");
                readWholeRam(records, &size);
                printf("=================================================\n");

                printf("Which specific Record do you want to delete?\n");
                int deleteColumnNo;
                scanf("%d", &deleteColumnNo);


                if(deleteColumnNo < 0 || deleteColumnNo > size){
                    printf("Input out of bounds\n");
                    response = -1;
                    break;
                }

                deleteRecordInRamByIndex(&records, &size, deleteColumnNo - 1);
                printf("Record deleted at index %d\n", deleteColumnNo);

                printf("This is the edited database at the moment: \n");
                printf("=================================================\n");
                readWholeRam(records, &size);
                printf("=================================================\n");

                response = -1;

                break;
            case 4:
                printf("Choose a filtering option which will only show certain records:\n1: Filter by Category\n2: Filter by Priority\n3: Filter by Status\n4: Filter by Time interval");
                scanf("%d", &response);

                if(response < 0 || response > 4){
                    printf("Choice out of bounds\n");
                    response = -1;
                    break;
                }

                switch(response){
                    case 1:
                        printf("By what category do you want to filter by?\n1: Work\n2: Hobby\n3: Home\n4: Other");
                        scanf("%d", &response);

                        if(response < 0 || response > 4){
                            printf("Choice out of bounds\n");
                            response = -1;
                            break;
                        }

                        if(response == 1){
                            filterByCategory(&records, &size, "Work");
                        } else if (response == 2){
                            filterByCategory(&records, &size, "Hobby");
                        } else if (response == 3){
                            filterByCategory(&records, &size, "Home");
                        } else {
                            filterByCategory(&records, &size, "Other");
                        }

                        response = -1;

                        break;
                    case 2:
                        printf("By what priority level do you want to filter by?\n1: 1(Very urgent)\n2: 2(Urgent)\n3: 3(Not Urgent)");
                        scanf("%d", &response);

                        if(response < 0 || response > 3){
                            printf("Choice out of bounds\n");

                            break;
                        }

                        if(response == 1){
                            filterByPriority(&records, &size, 1);
                        } else if(response == 2){
                            filterByPriority(&records, &size, 2);
                        } else {
                            filterByPriority(&records, &size, 3);
                        }
                        response = -1;
                        break;
                    case 3:
                        printf("By what status do you want to filter by?\n1: Complete\n2: In Progress\n3: No Status");
                        scanf("%d", &response);

                        if(response < 0 || response > 3){
                            printf("Choice out of bounds\n");
                            response = -1;
                            break;
                        }

                        if(response == 1){
                            filterByStatus(&records, &size, "Complete");
                        } else if(response == 2){
                            filterByStatus(&records, &size, "In Progress");
                        } else {
                            filterByStatus(&records, &size, "No Status");
                        }
                        break;

                        response = -1;
                    case 4:
                        printf("How do you want to filter by time?\n1: Completion date within x days\n2: Completion date after x days\n3: By dates that are overdue");
                        scanf("%d", &response);

                        if(response < 0 || response > 3){
                            printf("Choice out of bounds\n");
                            response = -1;
                            break;
                        }

                        if(response == 1) {
                            printf("Enter a time frame in terms of days (example: 5): \n");
                            scanf("%d", &response);
                            filterByTimeLesserThan(&records, &size, (double)response);

                        } else if(response == 2) {
                            printf("Enter a time frame in terms of days (example: 5): \n");
                            scanf("%d", &response);
                            filterByTimeGreaterThan(&records, &size, (double)response);
                        } else {
                            filterByTimeOverdue(&records, &size);
                        }
                        response = -1;
                        break;
                    default:
                        break;
                }
                break;
            default:
                printf("\nInvalid choice. Please try again. \n");
                response = -1;
        }
    }

    // Free the dynamically allocated memory
    freeDynamicArray(records);


    return 0;
}

