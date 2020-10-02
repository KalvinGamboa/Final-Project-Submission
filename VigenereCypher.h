#ifndef __VIGENERECYPHER_H__
#define __VIGENERECYPHER_H__

#define PASSWORD_LENGTH 256

class VigenereCypher{
private:
    int x;
    int y;
    int i,j;
    char encrypted[PASSWORD_LENGTH];
public:
    char *encrypt(char pass[],char key[]);
    char *decrypt(char pass[],char key[]);

};
#endif