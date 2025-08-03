#include <stdio.h>
#include <ctype.h>

int createNewFile(const char *fileName){
    FILE *fptr = fopen(fileName,"w");

    if(!fptr){
        printf("error in creating new file");
        return 1;
    }

    char ch;

    printf("Enter numbers (press any non-numeric key to stop):\n");
    while (1) {
        int number;
        if (scanf("%d", &number) != 1) {
            // Non-numeric input detected
            while ((ch = getchar()) != '\n' && ch != EOF); // Clear input buffer
            break;
        }
        fprintf(fptr, "%d\n", number);
    }


    

    fclose(fptr);
    return 0;
}


int readingFileAndFindingEven(const char *fileName , const char *evenfileName){
    FILE *fptr = fopen(fileName ,"r");
    FILE *evenPtr = fopen(evenfileName , "w");

    if(!fptr || !evenPtr){
        printf("Error in Opening files");
        return 1;
    }

    int number;
    while(fscanf(fptr , "%d" , &number) == 1)
        if( (number & 1) == 0)
            fprintf(evenPtr , "%d\n" , number);
    
    fclose(fptr);
    fclose(evenPtr);

    return 0;
}

int readingFile(const char *filename){
    FILE *fptr = fopen(filename , "r");

    if(!fptr){
        // printf("Error in opening file");
        return 1;
    }

    int number;
    while (fscanf(fptr , "%d" , &number) == 1 )
        printf("%d\n",number);
    
    fclose(fptr);
    return 0;
}

int main(){

    const char *fileName = "demo.txt";
    const char *evenfileName = "even.txt";


    if( createNewFile(fileName) == 1 || readingFileAndFindingEven(fileName , evenfileName ) == 1  )  return 1;

    printf("\n\nContent file\n");
    if(readingFile(fileName) == 1){
        printf("error in opening content file");
        return 1;
    }
    
    printf("\n\nContent of even  file\n");
    if(readingFile(evenfileName) == 1){
        printf("error in opening content file");
        return 1;
    }

    return 0;
}