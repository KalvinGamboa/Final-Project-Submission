#include "account.h"
#include <string.h>

account::account()
{

}

account::account(char* user, char* pass, char* site, bool cipher)
{
    strcpy(username, user);
    strcpy(password, pass);
    strcpy(siteName, site);
    hasCipher = cipher;
}
// char user[50], char pass[50], char site[50], bool cipher
