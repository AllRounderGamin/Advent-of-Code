#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void part1(){
    FILE *input;
    input = fopen("input.txt", "r");
    char inputStr[1024];
    long counter = 0;
    while(fgets(inputStr, 1024, input)){
        int digit1 = 0, digit2 = 0;
        char * index;
        inputStr[strcspn(inputStr, "\n")] = '\0';
        char *strToCheck = inputStr;
        for (int i = 9; i > 0; i--){
            if (index = strchr(strToCheck, i + 48)){
                //printf("index of %d: %ld, of string len: %d\n", i, index-inputStr, strlen(inputStr));
                if (index-inputStr == strlen(inputStr) - 1 || digit1 != 0){
                    digit2 = i;
                } else {
                    digit1 = i;
                    i++;
                    strToCheck = index+1;
                }
            }
            if (digit1 != 0 && digit2 != 0){
                //printf("%d, %d for %s\n", digit1, digit2, inputStr);
                break;
            }
        }
        counter += digit1*10 + digit2;
        //printf("%ld, += %d, %d for %s\n", counter, digit1, digit2, inputStr);
    }
    printf("PART 1 SOLUTION: %ld\n", counter);
}

// loop start at 9 count down, find index of number 9, if none found find index of 8 then 7 then...
// if largest int found is found at end of string it becomes the second digit and loop repeats 
// if LiF is not last char then only search remainder of string for the next large int 

int main(int argc, char *argv[]){
    part1();
    return 0;
}