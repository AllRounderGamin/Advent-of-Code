#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main (int argc, char *argv[]){
    FILE *input;
    input = fopen("input.txt", "r");
    char rotation[8];
    int position = 50;
    int counter1 = 0;
    int counter2 = 0;

    while(fgets(rotation, 8, input)){
        int overflow = 0;
        int startPos = position;
        if (rotation[0] == 'L'){
            position = position - strtol(&rotation[1], NULL, 10);
            while (position < 0){
                position = 100 + position;
                if (startPos != 0){
                    counter2++;
                }
                startPos = position;
            }
        } else if (rotation[0] == 'R'){
            position = position + strtol(&rotation[1], NULL, 10);
            while (position > 99){
                position = position - 100;
                if (position != 0){
                    counter2++;
                }
            }
        }
        // Above removed or added 100 to factor in starting at 0
        if (position == 0){
            counter1++;
            counter2++;
        }
    }
    printf("SOLUTION\nDay 1: %d\nDay2: %d\n", counter1, counter2);

    return 0;
}
