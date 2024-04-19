#include <stdio.h>
#include <stdlib.h>
#include "lecture/lecture.h"
#include <string.h>

#define DELIMITEUR ';'

char* RecupererToken(char chaine[], char delimiteur);

int main() {

    char chaine[] = "LORIS;PAGNAN";

    char* token = RecupererToken(chaine, DELIMITEUR);
    printf("Token : %s\n", token);

    return 0;
}

char* RecupererToken(char chaine[], char delimiteur)
{
    int i = 0;
    while (chaine[i] != delimiteur && i < strlen(chaine))
    {
        i++;
    }

    char* token = (char*)malloc((i + 1) * sizeof(char));
    if (token == NULL)
    {
        printf("Erreur d'allocation.\n");
        exit(1);
    }

    strncpy(token, chaine, i);
    token[i] = '\0';
    return token;
}

