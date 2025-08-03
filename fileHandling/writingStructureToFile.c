#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    printf("Enter marks of subject 2: ");
    scanf("%f", &st.subject2);

    st.total = st.subject1 + st.subject2;
    st.avg = st.total / 2.0;

    return st;
}

int AddingDetails(const char* fileName){
    FILE *fptr;

    // Try to open for reading to check existence
    printf("Checking if file exists...\n");
    fptr = fopen(fileName, "rb");
    if (fptr) {
        fclose(fptr);
        // File exists, open for appending
        fptr = fopen(fileName, "ab");
        printf("File exists.\nAdding new details.\n");
    } 
    else {
        // File does not exist, create new
        fptr = fopen(fileName, "wb");
        printf("File does not exist.\nCreating new file.\n");
    }

    if (!fptr) {
        printf("Error in opening/creating file\n");
        return 1;
    }

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
    FILE *fptr = fopen(fileName, "rb");
    if (!fptr) {
        printf("Error in opening file or file doesn't exist\n");
        return 1;
    }

    STUDENT st;
    printf("Displaying student details:\n");
    while (fread(&st, sizeof(STUDENT), 1, fptr)) {
        printf("Roll No: %d\n", st.RollNo);
        printf("Name: %s\n", st.name);
        printf("Subject 1 Marks: %.2f\n", st.subject1);
        printf("Subject 2 Marks: %.2f\n", st.subject2);
        printf("Total Marks: %.2f\n", st.total);
        printf("Average Marks: %.2f\n", st.avg);
        printf("-----------------------------\n");
    }

    fclose(fptr);
    return 0;
}

int main(){

    char fileName[256];

    printf("Welcome to Student Management System\n");

    //Taking file name input
    printf("Enter the file name you want to work on (without extension): ");
    scanf("%255s", fileName);
    // Append .dat extension
    strcat(fileName, ".dat");
    

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
                if(DisplayDetails(fileName)) return 1;
                printf("Details displayed successfully.\n");
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