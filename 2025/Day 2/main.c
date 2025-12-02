#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

int numOfDigits(long num){
    int digits = 0;
    do {
        num /= 10;
        digits++;
    } while (num != 0);
    return digits;
}

void part1_stringMethod(){  //First solution. Time: 0.087s 
    FILE *input;
    input = fopen("input.txt", "r");
    char inputStr[1024];
    fgets(inputStr, 1024, input);
    char *inputRanges = strtok(inputStr, ",");
    long counter1 = 0;
    while (inputRanges != NULL){
        char buffer[20];
        char* rangePtr;
        char* number = strtok_r(inputRanges, "-", &rangePtr);
        strcpy(buffer, number);
        long num1 = strtol(buffer, NULL, 10);
        number = strtok_r(NULL, "-", &rangePtr);
        strcpy(buffer, number);
        long num2 = strtol(buffer, NULL, 10);

        for (long i = num1; i < num2+1; i++){
            char numToCheck[256];
            char half1[128];
            char half2[128];
            sprintf(numToCheck, "%ld", i);
            if (strlen(numToCheck) % 2 == 0){
                int midPoint = strlen(numToCheck) / 2;
                strncpy(half1, numToCheck, midPoint);
                strncpy(half2, numToCheck+midPoint, midPoint);
                if (strcmp(half1, half2) == 0){
                    counter1 = counter1 + i;
                }
            }
            memset(half1, '\0', sizeof(half1));
            memset(half2, '\0', sizeof(half2));
        }
        inputRanges = strtok(NULL,  ",");
    }
    printf("Part 1: %ld\n", counter1);
    fclose(input);
}

void part1_mathsMethod(){  //Updated solution. Time: 0.032s 
    FILE *input;
    input = fopen("input.txt", "r");
    char inputStr[1024];
    fgets(inputStr, 1024, input);
    char *inputRanges = strtok(inputStr, ",");
    long counter1 = 0;
    while (inputRanges != NULL){
        char buffer[20] = {'\0'};
        char *dashPtr = strchr(inputRanges, '-');
        strncpy(buffer, inputRanges, dashPtr-inputRanges);
        long num1 = strtol(buffer, NULL, 10);
        strncpy(buffer, dashPtr+1, 20);
        long num2 = strtol(buffer, NULL, 10); 

        for (long i = num1; i < num2+1; i++){
            int digits = numOfDigits(i);
            if (digits % 2 == 0){
                int divisor = pow(10, digits/2);
                if (i / divisor == i % divisor){
                    counter1 += i;
                }
            }
        }
        inputRanges = strtok(NULL,  ",");
    }
    printf("Part 1: %ld\n", counter1);
    fclose(input);
}

void part2(){  //With optimisations from updated part 1. Time: 1.054s 
    FILE *input;
    input = fopen("input.txt", "r");
    char inputStr[1024];
    fgets(inputStr, 1024, input);
    char *inputRanges = strtok(inputStr, ",");
    long counter2 = 0;

    while (inputRanges != NULL){
        char buffer[20] = {'\0'};
        char *dashPtr = strchr(inputRanges, '-');
        strncpy(buffer, inputRanges, dashPtr-inputRanges);
        long num1 = strtol(buffer, NULL, 10);
        strncpy(buffer, dashPtr+1, 20);
        long num2 = strtol(buffer, NULL, 10); 

        for (long i = num1; i < num2+1; i++){
            int digits = numOfDigits(i);
            for (int j = 1; j < digits/2+1; j++){
                int divisor = pow(10, j);
                int modulo = i % divisor;
                if (modulo == 0){
                    continue;
                }
                int checkNum = 0;
                int intDiv = i / divisor;
                for (int k = 0; k < numOfDigits(intDiv) / numOfDigits(modulo)+1; k++){
                    checkNum += pow(divisor, k);
                }
                if (i / modulo == checkNum){
                    counter2 += i;
                    break;
                }
            }
        }
        inputRanges = strtok(NULL,  ",");
    }
    printf("Part 2: %ld\n", counter2);
    fclose(input);
}

int main(int argc, char *argv[]){
    part1_mathsMethod();
    part2();

    return 0;
}
