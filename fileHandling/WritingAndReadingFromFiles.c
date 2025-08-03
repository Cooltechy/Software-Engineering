#include <stdio.h>
#define MAXSIZE  100

int createNewFile(){
    FILE *fptr = fopen("demo.txt","w");

    if(!fptr){
        printf("error in creating new file");
        return 1;
    }

    fprintf(fptr , "Hello! Welcome to the world of Files.\nHey this file is created using c.");

    fclose(fptr);
    return 0;
}

int readingFile(){
    FILE *fptr = fopen("demo.txt","r");

    if(!fptr){
        printf("error in opening file");
        return 1;
    }

    char buffer[MAXSIZE];
    
    while(fgets(buffer , MAXSIZE , fptr))    
        printf("%s",buffer);
    

    fclose(fptr);
}
 
int main(){
    
    if(createNewFile() == 1)    return 1;

    if(readingFile() == 1)      return 1;

    

    return 0;
}