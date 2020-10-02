#define PASSWORD_LENGTH 256

class AtbashCypher{
private:
    int x;
    int i;
    char encrypted[PASSWORD_LENGTH];
public:
    char *encrypt(char pass[]);
};
