// https://stackoverflow.com/questions/3893937/sorting-an-array-in-c
// https://stackoverflow.com/questions/56966432/is-there-a-binary-search-method-in-the-c-standard-library

// store the beginning and end of the ranges as range obj and sort by the beginning number, search array for closest beginning then subtract num to check
// from the end of the range, if minus its within if not its not

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Range {
    long min;
    long max;
};

int compare(const void *s1, const void *s2) {
    struct Range *r1 = (struct Range *)s1;
    struct Range *r2 = (struct Range *)s2;
    if (r1->min < r2->min)  /* same gender so sort by id */
        return -1;
    else
        return 1;
}

void part1(){
    FILE *input;
    input = fopen("input.txt", "r");
    char inputStr[1024];
    struct Range ranges[192] = {[0 ... 192-1] = {-1, -1} };
    fgets(inputStr, 1024, input);
    int index = 0;
    // make range array
    while (strlen(inputStr) != 1){
        char buffer[20] = {'\0'};
        char *rangePtr = strchr(inputStr, '-');
        strncpy(buffer, inputStr, rangePtr-inputStr);
        ranges[index].min = strtol(buffer, NULL, 10);
        strncpy(buffer, rangePtr+1, 20);
        ranges[index].max = strtol(buffer, NULL, 10); 
        index++;
        fgets(inputStr, 1024, input);
    }
    qsort(ranges, sizeof(ranges) / sizeof(ranges[0]), sizeof(ranges[0]), compare);
    // check ingredients
    int counter = 0;
    while (fgets(inputStr, 1024, input)){
        char buffer[20] = {'\0'};
        long numToCmp;
        strncpy(buffer, inputStr, 20);
        numToCmp = strtol(buffer, NULL, 10);
        for (int i = 0; i < 192; i++){
            if (ranges[i].min < numToCmp){
                if (ranges[i].max > numToCmp){
                    counter++;
                    break;
                }
            } else {
                break;
            }
        }
    }
    printf("PART 1 SOLUTION: %d\n", counter);
}

void part2(){
    FILE *input;
    input = fopen("input.txt", "r");
    char inputStr[1024];
    struct Range ranges[192] = {[0 ... 192-1] = {-1, -1} };
    fgets(inputStr, 1024, input);
    int index = 0;
    // make range array
    while (strlen(inputStr) != 1){
        char buffer[20] = {'\0'};
        char *rangePtr = strchr(inputStr, '-');
        strncpy(buffer, inputStr, rangePtr-inputStr);
        ranges[index].min = strtol(buffer, NULL, 10);
        strncpy(buffer, rangePtr+1, 20);
        ranges[index].max = strtol(buffer, NULL, 10); 
        index++;
        fgets(inputStr, 1024, input);
    }
    qsort(ranges, sizeof(ranges) / sizeof(ranges[0]), sizeof(ranges[0]), compare);
    // count ids
    long counter = 0;
    long highest = 0;
    for (int i = 0; i < 192; i++){
        if (ranges[i].min < highest){
            if (ranges[i].max > highest){
                counter += ranges[i].max - highest;
                highest = ranges[i].max;
            }
        } else if (ranges[i].min > highest){
            counter += ranges[i].max - ranges[i].min + 1;
            highest = ranges[i].max;
        } else{
            counter += ranges[i].max - ranges[i].min;
            highest = ranges[i].max;
        }
    }

    printf("PART 2 SOLUTION: %ld\n", counter);
}

/* faster method for part 2 for future reference 
    #include <math.h>
    start = fmax(ranges[i].min, highest)
    end = fmax(ranges[i].max, highest)
    counter += end - start
    highest = end
    // if range should not be included then start - end is 0
    // above example uses fmax but due to type conversions may be easier to define 2 macros
*/


int main(int argc, char *argv[]){
    part1();
    part2();

    return 0;
}