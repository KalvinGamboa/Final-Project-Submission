#include "generatedPassword.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctime>

generatedPassword::generatedPassword(int length, bool allowSpecChar)
{
    int start;
    int maxi;
    char gen[length+1];
    srand(time(NULL));
    if (allowSpecChar == true){
        start = 33;
        maxi = 91;
        for(int x = 0; x <= length; x++){
            char randChar = start+(rand() % maxi);
            while(randChar == 96){
                randChar = start+(rand() % maxi);
            }
            gen[x] = randChar;
        }
    }else{
        start = 48;
        maxi = 75;
        for(int x = 0; x <= length; x++){
            char randChar = start + (rand() % maxi);
            while((randChar > 90 && randChar < 97)||(randChar > 57 && randChar < 65)){
                randChar = start + (rand() % maxi);
            }
            gen[x] = randChar;
        }
    }
    gen[length] = '\0';
    strcpy(password, gen);
}
