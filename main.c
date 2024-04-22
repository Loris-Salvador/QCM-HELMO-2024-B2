#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITEUR ';'

char* RecupererToken(char chaine[], char delimiteur);
void ExtraireInformations(char ligne[], char** question, int* nbPropositions, char*** propositions, float** points);

int main() {

    char ligne[] = "Quelle est la capitale de la Belgique ?;3;Liege;Anvers;Bruxelles;-0.5;-0.5;1";
    char* question;
    int nbPropositions;
    char** propositions;
    float* points;

    ExtraireInformations(ligne, &question, &nbPropositions, &propositions, &points);

    printf("\nQuestion: %s\n", question);
    printf("Nombre de propositions: %d\n", nbPropositions);

    printf("Propositions:\n");
    for (int i = 0; i < nbPropositions; i++) {
        printf("%s\n", propositions[i]);
    }

    printf("Points:\n");
    for (int i = 0; i < nbPropositions; i++) {
        printf("%.1f\n", points[i]);
    }

    for (int i = 0; i < nbPropositions; i++) {
        free(propositions[i]);
    }

    free(propositions);
    free(points);

    return 0;
}

char* RecupererToken(char chaine[], char delimiteur) {
    int i = 0;
    while (chaine[i] != delimiteur && i < strlen(chaine)) {
        i++;
    }

    char* token = (char*)malloc((i + 1) * sizeof(char));
    if (token == NULL) {
        printf("Erreur d'allocation.\n");
        exit(1);
    }

    strncpy(token, chaine, i);
    token[i] = '\0';
    return token;
}

void ExtraireInformations(char ligne[], char** question, int* nbPropositions, char*** propositions, float** points) {
    char* ptrLigne = ligne;

    *question = RecupererToken(ptrLigne, DELIMITEUR);

    ptrLigne = ptrLigne + strlen(*question) + 1;

    char* nbProp = RecupererToken(ptrLigne, DELIMITEUR);

    int nbPropInt = atoi(nbProp);
    *nbPropositions = nbPropInt;

    ptrLigne = ptrLigne + strlen(nbProp) + 1;

    free(nbProp);

    *propositions = (char**)malloc(nbPropInt * sizeof(char*));

    for (int i = 0; i < nbPropInt; i++) {
        (*propositions)[i] = RecupererToken(ptrLigne, DELIMITEUR);
        ptrLigne += strlen((*propositions)[i]) + 1;
    }

    *points = (float*)malloc(nbPropInt * sizeof(float));

    for (int i = 0; i < nbPropInt; i++) {
        char* tmp = RecupererToken(ptrLigne, DELIMITEUR);
        (*points)[i] = atof(tmp);
        ptrLigne = ptrLigne + strlen(tmp) + 1;
        free(tmp);
    }
}
