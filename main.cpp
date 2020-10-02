#include <stdio.h>
#include <string.h>
#include <iostream>
#include <ctype.h>
#include "account.h"
#include "VigenereCypher.h"
#include "CaesarCypher.h"
#include "AtbashCypher.h"
#include "generatedPassword.h"

//main function of the code.
void passwordManager();
//reads accounts from the csv file
void readAccounts();
//saves accounts to a csv file
void saveAccounts();
//displays all accounts to the user
void viewAccounts();
//decrypts passwords in account
void encryptAccount(char*);
void decryptAccount(char*);
//turns array into all null
void clearArray(int, char*);
//creates a password
void createPassword(char*);
//ask for an integer input from user
int askChoice(const char*, int, int);
int input = 0;
//number of accounts
int accountNum = 0;
//user input for account data
char userIn[21] = {0}, passIn[21] = {0}, siteIn[21] = {0};
//where all the acccounts are saved
account acc[50];
//cypher input data
int shift = 0;
char key[20];
//cypher modules
VigenereCypher vig;
CaesarCypher cae;
AtbashCypher atb;
//Program loop value, turned false if the user wants the program to stop.
bool running = true;
using namespace std;
int main(){
    readAccounts();
    while(running == true){
        passwordManager();
    }
	return 0;
}

void passwordManager(){
    viewAccounts();
    input = askChoice("\nPlease select an option:\n1 - Generate new account info\n2 - Encrypt account info\n3 - Decrypt account info\n4 - Create new password\n5 - Quit\n> ", 1, 5);
    bool finished = false;
    int acct = 0;
    switch(input){
    case 1:
        while(finished == false){
            printf("\nPlease input username:\n>");
            scanf("%[^\n]", userIn); fflush(stdin);
            input = askChoice("\nGenerate password?: 1 - Yes / 2 - No\n>", 1, 2);
            if(input == 1){
                createPassword(passIn);
            }else{
                printf("\nPlease input password:\n>");
                scanf("%[^\n]", passIn); fflush(stdin);
            }
            printf("\nPlease input site name:\n>");
            scanf("%[^\n]", siteIn); fflush(stdin);
            account accIn(userIn, passIn, siteIn, false);
            printf("\nSite: %s\nUser: %s\nPass: %s\n\n", accIn.siteName, accIn.username, accIn.password);
            input = askChoice("\nIs this info correct?: 1 - Yes / 2 - No\n>", 1, 2);
            if(input == 1){
                finished = true;
            }
            acc[accountNum] = accIn;
            printf("\n%d:\nUser: %s\nPass: %s\nSite: %s\n", accountNum+1, acc[accountNum].username, acc[accountNum].password, acc[accountNum].siteName);
            accountNum++;
        }
        saveAccounts();
        break;
    case 2:
        char passwordencrypt[20];
        while(finished == false){
            input = 1;
            if(input == 1){
                viewAccounts();
                acct = askChoice("\nChoose account to encrypt password\n>", 1, accountNum);
                acct--;
                if(acc[acct].hasCipher != true){
                    strcpy(passwordencrypt, acc[acct].password);
                    printf("\n%s", passwordencrypt);
                    encryptAccount(passwordencrypt);
                    printf("\n%s", passwordencrypt);
                    int save = askChoice("\nReplace password from existing accounts?: 1 - Yes / 2 - No\n>", 1, 2);
                    if(save == 1){
                        strcpy(acc[acct].password, passwordencrypt);
                        acc[acct].hasCipher = true;
                        finished = true;
                    }
                }
                else{
                    printf("\nPassword already encrypted\n");
                }
                input = askChoice("\nContinue with another new password?: 1 - Yes / 2 - No\n>", 1, 2);
                if (input == 2){
                    finished = true;
                }
            }
        }
        saveAccounts();
        break;
    case 3:
        char passworddecrypt[20];
        while(finished == false){
            input = 1;
            if(input == 1){
                viewAccounts();
                acct = askChoice("\nChoose account to decrypt password\n>", 1, accountNum);
                acct--;
                if(acc[acct].hasCipher != false){
                    strcpy(passworddecrypt, acc[acct].password);
                    printf("\n%s", passworddecrypt);
                    decryptAccount(passworddecrypt);
                    printf("\n%s", passworddecrypt);
                    int save = askChoice("\nReplace password from existing accounts?: 1 - Yes / 2 - No\n>", 1, 2);
                    if(save == 1){
                        strcpy(acc[acct].password, passworddecrypt);
                        acc[acct].hasCipher = false;
                        finished = true;
                    }
                }else{
                    printf("\nPassword already decrypted\n");
                }
                input = askChoice("\nContinue with another new password?: 1 - Yes / 2 - No\n>", 1, 2);
                if (input == 2){
                    finished = true;
                }
            }
        }
        saveAccounts();
        break;
    case 4:
        while(finished == false){
            char pass[20];
            createPassword(pass);
            input = askChoice("\nReplace password from existing accounts?: 1 - Yes / 2 - No\n>", 1, 2);
            if(input == 1){
                viewAccounts();
                input = askChoice("\nChoose account to replace password\n>", 1, accountNum);
                strcpy(acc[input].password, pass);
                input = askChoice("\nContinue with another new password?: 1 - Yes / 2 - No\n>", 1, 2);
                if (input == 2){
                    finished = true;
                }
            }else{
                finished = true;
            }
        }
        saveAccounts();
        break;
    default:
        running = false;
        break;
    }
}


int askChoice(const char question[], int mini, int maxi){
    int in;
    do{
        printf("%s", question);
        scanf("%d", &in);
    }while(in < mini || in > maxi);
    fflush(stdin);
    return in;
}

void encryptAccount(char* accountpass){
    char* password;
    char keyInput[20];
    input = askChoice("\nPlease select encryption option:\n1 - Vigenere Cypher\n2 - Caesar Cypher\n3 - Atbash Cypher\n4 - Return\n> ", 1, 4);
    switch(input){
        case 1:
            {
                printf("\nPlease input key:\n>");
                scanf("%[^\n]", key);
                password = vig.encrypt(accountpass,key);
                strcpy(accountpass,password);
                break;
            }
        case 2:
            {
                input = askChoice("\nPlease input shift:\n>",1,26);
                shift = input;
                password = cae.encrypt(accountpass,shift);
                strcpy(accountpass,password);
                break;
            }

        case 3:
            {
                password = atb.encrypt(accountpass);
                strcpy(accountpass,password);
                break;
            }
    }
}
void decryptAccount(char* accountpass){
    char* password;
    char keyInput[20];
    input = askChoice("\nPlease select decryption option:\n1 - Vigenere Cypher\n2 - Caesar Cypher\n3 - Atbash Cypher\n4 - Return\n> ", 1, 4);
    switch(input){
        case 1:
            {
                printf("\nPlease input key:\n>");
                scanf("%[^\n]", key);
                password = vig.decrypt(accountpass,key);
                strcpy(accountpass,password);
                break;
            }
        case 2:
            {
                input = askChoice("\nPlease input shift:\n>",1,26);
                shift = input;
                password = cae.decrypt(accountpass,shift);
                strcpy(accountpass,password);
                break;
            }

        case 3:
            {
                password = atb.encrypt(accountpass);
                strcpy(accountpass,password);
                break;
            }

    }
}

void readAccounts(){
    char accountInfo[256];
    account readAcc;

    FILE *fp;
    fp = fopen("accounts.csv", "r");
    fgets(accountInfo, 256, fp);
    while(fgets(accountInfo, 256, fp)){
        int pos = 0;
        int length = 0;
        int section = 0;
        char test[2];
        for(int y = 1; y < 5; y++){
            char reader[20];
            int x = 0;
            while(accountInfo[pos]!=','){
                if(accountInfo[pos] == '\n'){
                    break;
                }
                reader[x] = accountInfo[pos];
                pos++;
                x++;
                length = x;
            }
            reader[length] = '\0';
            switch(y){
                case 1:
                    strcpy(readAcc.username, reader);
                    break;
                case 2:
                    strcpy(readAcc.password, reader);
                    break;
                case 3:
                    strcpy(readAcc.siteName, reader);
                    break;
                case 4:
                    if(reader[0] == 'T'){
                        readAcc.hasCipher = true;
                    }else if (reader[0] == 'F'){
                        readAcc.hasCipher = false;
                    }else{
                        readAcc.hasCipher = false;
                    }
                    break;
                default:
                    break;
            }
            pos++;
        }
        acc[accountNum] = readAcc;
        accountNum++;
    }
    fclose(fp);
}

void createPassword(char* outPass){
    bool running = true;
    while(running == true){
        int passLength = askChoice("\nHow long do you want the generated password to be?: Max is 20\n>", 1, 20);
        input = askChoice("\nAllow special characters?: 1 - Yes / 2 - No\n>", 1, 2);
        bool allowSpec = true;
        if(input == 2){
            allowSpec = false;
        }
        generatedPassword pass(passLength, allowSpec);
        printf("\n%s", pass.password);
        input = askChoice("\nRetry random generator?: 1 - Yes / 2 - No\n>", 1, 2);
        if(input == 2){
            running = false;
            strcpy(outPass, pass.password);
        }
    }
}

void clearArray(int length, char* badArray){
    for(int x = 0; x < length; x++){
        badArray[x] = 0;
    }
}

void saveAccounts(){
    FILE *fp;
    fp = fopen("accounts.csv", "w");
    fprintf(fp, "Username,Password,Site,Cipher\n");
    for(int x = 0; x < accountNum; x++){
        char accountInfo[256] = {0};
        strcat(accountInfo, acc[x].username);
        strcat(accountInfo, ",");
        strcat(accountInfo, acc[x].password);
        strcat(accountInfo, ",");
        strcat(accountInfo, acc[x].siteName);
        strcat(accountInfo, ",");
        if(acc[x].hasCipher == true){
            strcat(accountInfo, "T\n");
        }else{
            strcat(accountInfo, "F\n");
        }
        fprintf(fp, accountInfo);
    }
    fclose(fp);
}

void viewAccounts(){
    printf("#\tUSERNAME - PASSWORD - SITE - CIPHER\n");
    printf("-------------------------------------\n");
    for(int x = 0; x < accountNum; x++){
        if(acc[x].hasCipher == true){
            printf("%d\t%s - %s - %s - T\n", x+1, acc[x].username, acc[x].password, acc[x].siteName);
        }else{
            printf("%d\t%s - %s - %s - F\n", x+1, acc[x].username, acc[x].password, acc[x].siteName);
        }

    }
}
