#define PASSWORD_LENGTH 256

class CaesarCypher{
private:
    int i;
    int x;
    char encrypted[PASSWORD_LENGTH];
public:
    char *encrypt(char pass[] ,int shift);
    char *decrypt(char pass[] ,int shift);
};
