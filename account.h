#ifndef ACCOUNT_H
#define ACCOUNT_H


class account{
    public:
        account();
        account(char* user, char* pass, char* site, bool cipher);
        char username[50];
        char password[50];
        char siteName[50];
        bool hasCipher;
};

#endif // ACCOUNT_H
