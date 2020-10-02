#include "CaesarCypher.h"
#include <string.h>

char *CaesarCypher::encrypt(char* pass, int key){
    x = strlen(pass);
    char character;

    for( i = 0; i < x; ++i){
		character = pass[i];
		if(character >= 'a' && character <= 'z'){
			encrypted[i] = ((character + key + 'a'  - 12) % 26) + 'a';
		}
		else if(character >= 'A' && character <= 'Z'){
			encrypted[i] = ((character + key + 'A') % 26) + 'A';
		}
        else if(character >= '0' && character <= '9'){
			encrypted[i] = ((character + key + '0' - 6) % 10) + '0';
		}
        else
        {
            encrypted[i] = pass[i];
        }
	}
    return encrypted;
}
char *CaesarCypher::decrypt(char* pass, int key){
    x = strlen(pass);
    char character;

    for( i = 0; i < x; ++i){
		character = pass[i];
		if(character >= 'a' && character <= 'z'){
			encrypted[i] = ((character - key + 'a'  - 12) % 26) + 'a';
		}
		else if(character >= 'A' && character <= 'Z'){
			encrypted[i] = ((character - key + 'A') % 26) + 'A';
		}
        else if(character >= '0' && character <= '9'){
			encrypted[i] = ((character - key + '0' + 6) % 10) + '0';
		}
        else
        {
            encrypted[i] = pass[i];
        }
	}
    return encrypted;
}