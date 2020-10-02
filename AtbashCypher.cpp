#include "AtbashCypher.h"
#include <string.h>

char *AtbashCypher::encrypt(char* pass){
    x = strlen(pass);
    char character;

    for( i = 0; i < x; ++i){
        character = pass[i];
		if(character >= 'a' && character <= 'z'){
			encrypted[i] = ((('z' - (character - 97)) + 'a' - 12) % 26) + 'a';
		}
		else if(character >= 'A' && character <= 'Z'){
			encrypted[i] = ((('Z' - (character - 65)) + 'A') % 26) + 'A';
		}
        else if(character >= '0' && character <= '9'){
			encrypted[i] = character;
		}
        else
        {
            encrypted[i] = pass[i];
        }
	}
    return encrypted;

}
