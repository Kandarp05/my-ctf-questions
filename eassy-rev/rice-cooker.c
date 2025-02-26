#include <stdio.h>
#include <string.h>

const char subs[] = "0123456789abcdefghijklmnopqrstuvwxyz_{}";
const char garbage_chars[] = "!@#$%^&*()";
const int SHIFT = 7;
const int XOR_KEY = 0xFF;
const char* expected = "6!!sbn*ass%84z@84c(8o_^4#_#8b0)5m_&j}y$vvw!h";

void substitute(char* str) {
    char temp[100];
    strcpy(temp, str);
    for(int i = 0; str[i]; i++)
        for(int j = 0; j < strlen(subs); j++)
            if(str[i] == subs[j]) {
                temp[i] = subs[(j + SHIFT) % strlen(subs)];
                break;
            }
    strcpy(str, temp);
}

void inflate(char* str) {
    char temp[200];
    int j = 0;
    for(int i = 0; str[i]; i++) {
        temp[j++] = str[i];
        if(i % 3 == 0)
            temp[j++] = garbage_chars[i % strlen(garbage_chars)];
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

void reverse(char* str) {
    for(int i = 0, len = strlen(str); i < len/2; i++) {
        char t = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = t;
    }
}

void transform(char* str) {
    for(int i = 0; str[i]; i++)
        str[i] = (~str[i] & 0xFF) ^ XOR_KEY;
}

int main() {
    char password[200];
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    substitute(password);
    inflate(password);
    reverse(password);
    transform(password);

    printf(strcmp(password, expected) == 0 ? "enjoy the rice… next time, it won’t be this easy. 🌾😈\n" : "no rice for you bro 🍚❌\n");
    return 0;
}