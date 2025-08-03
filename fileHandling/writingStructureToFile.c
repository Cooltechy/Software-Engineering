#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "fileUtils.h"


typedef struct student
{
    int RollNo;
    char name[100];
    float subject1;
    float subject2;
    float total;
    float avg;
}STUDENT;

STUDENT creatingNewStudentDetails(){
    STUDENT st;
    printf("Enter roll no: ");
    scanf("%d", &st.RollNo);
    printf("Enter name: ");
    getchar();  // to consume the newline character left by scanf
    fgets(st.name, sizeof(st.name), stdin);
    printf("Enter marks of subject 1: ");
    scanf("%f", &st.subject1);
    while (st.subject1 < 0 || st.subject1 > 100) {
        printf("Invalid marks for subject 1. Please enter again (0-100): ");
        scanf("%f", &st.subject1);
    }
    
    printf("Enter marks of subject 2: ");
    scanf("%f", &st.subject2);
    while (st.subject2 < 0 || st.subject2 > 100) {
        printf("Invalid marks for subject 2. Please enter again (0-100): ");
        scanf("%f", &st.subject2);
    }

    st.total = st.subject1 + st.subject2;
    st.avg = st.total / 2.0;

    return st;
}


int AddingDetails(const char* fileName){

    system("clear");

    FILE *fptr;

    // Try to open for reading to check existence
    printf("Opening file %s for adding details...\n", fileName);
    fptr = openFile(fileName, "ab");
    if (!fptr) {
        printf("Error in opening %s for writing.\n", fileName);
        return 1;
    }
    printf("%s opened successfully \nAdding details...\n", fileName);

    char ch ;
    do {
        STUDENT st = creatingNewStudentDetails();
        fwrite(&st, sizeof(STUDENT), 1, fptr);
        printf("Add another student? (y/n): ");
        scanf(" %c", &ch);
    } while (tolower(ch) == 'y');

    fclose(fptr);
    return 0;
}

int DisplayDetails(const char* fileName){
    
    system("clear");

    printf("Opening %s for displaying details...\n", fileName);
    FILE *fptr = openFile(fileName, "rb");
    if (!fptr) {
        printf("Error in opening %s for reading.\n", fileName);
        return -1;
    }
    printf("%s opened successfully for displaying details.\n\n", fileName);

    STUDENT st;
    int count = 0;
    printf("Displaying student details:\n\n");
    while (fread(&st, sizeof(STUDENT), 1, fptr)) {
        printf("Roll No: %d\n", st.RollNo);
        printf("Name: %s\n", st.name);
        printf("Subject 1 Marks: %.2f\n", st.subject1);
        printf("Subject 2 Marks: %.2f\n", st.subject2);
        printf("Total Marks: %.2f\n", st.total);
        printf("Average Marks: %.2f\n", st.avg);
        printf("-----------------------------\n");
        count++;
    }

    fclose(fptr);

    // if (count == 0) 
    //     printf("No student details found in %s.\n", fileName);
    // else 
    //     printf("Total %d student(s) displayed.\n", count);
    

    return count;
}

int main(){

    char fileName[256];

    printf("Welcome to Student Management System\n");

    //Taking file name input
    printf("Enter the file name you want to work on (without extension): ");
    scanf("%255s", fileName);
    // Append .dat extension
    strcat(fileName, ".dat");

    FILE *fptr;
    printf("Checking for existance of file: %s\n", fileName);
    if(!isFileExists(fileName)) {
        printf("File %s doesn't exists.\n", fileName);
        printf("Want to create a new file? (y/n): ");
        char choice;
        scanf(" %c", &choice);

        if (tolower(choice) == 'y') {
            fptr = createFile(fileName);
            if (fptr) {
                printf("File %s created successfully.\n", fileName);
                fclose(fptr);
            } else {
                printf("Error creating file %s.\n", fileName);
                return 1;
            }
        } 
        else {
            printf("Exiting program.\n");
            return 0;
        }
    }


    

    int choice;
    do {
        printf("\n1. Add Student Details\n2. Display Student Details\n3. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if(AddingDetails(fileName)) return 1;
                printf("Details added successfully.\n");
                break;
            case 2:
                int disp = DisplayDetails(fileName);    
                if(disp == -1) return 1;
                else if(disp > 0) printf("Details displayed of %d student(s) successfully.\n", disp);
                else printf("No record found.\n");
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);


    return 0;
}