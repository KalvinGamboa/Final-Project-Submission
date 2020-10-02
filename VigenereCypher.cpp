#include "VigenereCypher.h"
#include <stdio.h>
#include<string.h>

char *VigenereCypher::encrypt(char* pass,char* key)
{
    x = strlen(pass);
    y = strlen(key);
    char finkey[y];
    char character;

    // Keygen
    for(i = 0, j = 0; i < x; ++i, ++j){
        if(j >= y)
            j = 0;
        finkey[i] = key[j];
    }

    // Encryption
    for(i = 0; i < x; ++i){
        character = pass[i];
        if(character >= 'A' && character <= 'Z'){
        finkey[i] = finkey[i] - 32;
         encrypted[i] = ((character + finkey[i]) % 26) + 'A';
        }
        else if(character >= 'a' && character <= 'z'){
        encrypted[i] = ((character + finkey[i]  - 12) % 26) + 'a';
        }
        else{
            encrypted[i] = character;
        }

    }
    encrypted[i] = '\0';
    return encrypted;
}
char *VigenereCypher::decrypt(char* pass,char* key)
{
    x = strlen(pass);
    y = strlen(key);
    char finkey[y];
    char character;

    // Keygen
    for(i = 0, j = 0; i < x; ++i, ++j){
        if(j == y)
            j = 0;
        finkey[i] = key[j];
    }


    // Decryption
    for(i = 0; i < x; ++i){
        character = pass[i];
        if(character >= 'A' && character <= 'Z'){
        finkey[i] = finkey[i] - 32;
        encrypted[i] = ((character - finkey[i] + 26) % 26) + 'A';
        }
        else if(character >= 'a' && character <= 'z'){
        encrypted[i] = ((character - finkey[i]  + 26) % 26) + 'a';
        }
        else{
            encrypted[i] = character;
        }

    }
    encrypted[i] = '\0';
    return encrypted;
}
