#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lecture/lecture.h"

#define DELIMITEUR ';'
#define LGMAXLIGNE 512

char* RecupererToken(char chaine[], char delimiteur);
int ExtraireInformations(char ligne[], char** question, int* nbPropositions, char*** propositions, float** points);
char ** ExtraireFichierEnTableau(char nomFichier[], int* nbLigne);
int TirageAleatoire(int maximum, int tab[], int nbElements);
void FreeTabQcm(char** tabQcm, int nbLignes);
float RechercherMaximum(float tab[], int nbElements);


int main() {

    srand(time(NULL));

    int nbQuestions, nbLignes, numLigne, reponse, nbPropositions, retour, i;
    int questionsPosees = 0;
    int* tabQuestionsPosees;
    char* question;
    char* nomFichier;
    char** propositions;
    float* points;
    float total = 0;
    float maxPoints = 0;

    nomFichier = LireChaineDynamique("Entrez le nom du fichier : ");

    char** tabQcm = ExtraireFichierEnTableau(nomFichier, &nbLignes);
    free(nomFichier);
    if(tabQcm == NULL)
    {
        return 1;
    }

    do
    {
        LireEntier("\nCombien de questions voulez-vous : ", &nbQuestions);
        if(nbQuestions > nbLignes)
        {
            printf("Il n'y a pas assez de questions dans le fichier !");
        }
    } while (nbQuestions > nbLignes);

    tabQuestionsPosees = (int*)malloc(nbQuestions * sizeof(int));
    if (tabQuestionsPosees == NULL) {
        FreeTabQcm(tabQcm, nbLignes);
        printf("Erreur d'allocation Tableau questions posees.\n");
        return 1;
    }

    do
    {
        numLigne = TirageAleatoire(nbLignes, tabQuestionsPosees, nbQuestions);

        retour = ExtraireInformations(tabQcm[numLigne], &question, &nbPropositions, &propositions, &points);
        if(retour == 1)
        {
            free(tabQuestionsPosees);
            FreeTabQcm(tabQcm, nbLignes);
            return 1;
        }

        tabQuestionsPosees[questionsPosees] = numLigne;

        printf("\nQuestion: %s\n", question);

        printf("\nPropositions :\n");
        for (i = 0; i < nbPropositions; i++) {
            printf("%d : %s\n", i + 1, propositions[i]);
        }

        do {
            LireEntier("\nVotre Reponse : ", &reponse);
            if(reponse > nbPropositions || reponse < 1 )
            {
                printf("Aucune propositions ne correspond");
            }
        } while (reponse > nbPropositions || reponse < 1);

        total = total + points[reponse - 1];
        maxPoints = maxPoints + RechercherMaximum(points, nbPropositions);

        free(question);
        for (i = 0; i < nbPropositions; i++) {
            free(propositions[i]);
        }
        free(propositions);
        free(points);

        questionsPosees++;
    } while (questionsPosees < nbQuestions);


    printf("\nVotre Total : %.2f/%.2f", total, maxPoints);

    free(tabQuestionsPosees);

    FreeTabQcm(tabQcm, nbLignes);

    return 0;
}

char* RecupererToken(char chaine[], char delimiteur) {
    int i = 0;
    while (chaine[i] != delimiteur && i < strlen(chaine)) {
        i++;
    }

    char* token = (char*)malloc((i + 1) * sizeof(char));
    if (token == NULL) {
        return NULL;
    }

    strncpy(token, chaine, i);
    token[i] = '\0';
    return token;
}

int ExtraireInformations(char ligne[], char** question, int* nbPropositions, char*** propositions, float** points) {
    char* ptrLigne = ligne;

    *question = RecupererToken(ptrLigne, DELIMITEUR);
    if (question == NULL) {
        printf("Erreur d'allocation Token question.\n");
        return 1;
    }

    ptrLigne = ptrLigne + strlen(*question) + 1;

    char* nbPropStr = RecupererToken(ptrLigne, DELIMITEUR);
    int nbProp;
    sscanf(nbPropStr, "%d", &nbProp);
    *nbPropositions = nbProp;

    ptrLigne = ptrLigne + strlen(nbPropStr) + 1;

    free(nbPropStr);

    *propositions = (char**)malloc(nbProp * sizeof(char*));
    if (question == NULL) {
        free(*question);
        printf("Erreur d'allocation propositions.\n");
        return 1;
    }

    for (int i = 0; i < nbProp; i++) {
        (*propositions)[i] = RecupererToken(ptrLigne, DELIMITEUR);
        ptrLigne = ptrLigne + strlen((*propositions)[i]) + 1;
    }

    *points = (float*)malloc(nbProp * sizeof(float));
    if (question == NULL) {
        free(*propositions);
        free(*question);
        printf("Erreur d'allocation points.\n");
        return 1;
    }

    for (int i = 0; i < nbProp; i++) {
        char* tmp = RecupererToken(ptrLigne, DELIMITEUR);
        sscanf(tmp, "%f", &(*points)[i]);
        ptrLigne = ptrLigne + strlen(tmp) + 1;
        free(tmp);
    }

    return 0;
}

char ** ExtraireFichierEnTableau(char nomFichier[], int* nbLigne)
{
    FILE* fp;
    char** tab;
    char ligne[LGMAXLIGNE];

    fp = fopen(nomFichier, "r");
    if (fp == NULL)
    {
        printf("Impossible d'ouvrir le fichier !\n");
        return NULL;
    }

    *nbLigne = 0;
    while(fgets(ligne, LGMAXLIGNE + 1, fp) != NULL)
    {
        (*nbLigne)++;
    }

    tab = malloc((*nbLigne) * sizeof(char*));
    if (tab == NULL)
    {
        printf("Erreur d'allocation tableau\n");
        return NULL;
    }

    rewind(fp);
    int i = 0;

    while(fgets(ligne, LGMAXLIGNE + 1, fp) != NULL)
    {
        tab[i] = malloc((strlen(ligne) + 1) * sizeof(char));
        if (tab[i] == NULL)
        {
            printf("Erreur d'allocation ligne\n");
            return NULL;
        }
        strcpy(tab[i], ligne);
        tab[i][strlen(ligne)] = '\0';
        i++;
    }

    fclose(fp);
    return tab;
}

int TirageAleatoire(int maximum, int tab[], int nbElements) {
    int retry, nb;

    do
    {
        retry = 0;
        nb =  rand() % maximum;

        for(int i = 0; i < nbElements; i++)
        {
            if(nb == tab[i])
            {
                retry = 1;
            }
        }
    } while (retry == 1);

    return nb;
}

void FreeTabQcm(char** tabQcm, int nbLignes)
{
    for (int i = 0; i < nbLignes; i++) {
        free(tabQcm[i]);
    }
    free(tabQcm);
}

float RechercherMaximum(float tab[], int nbElements)
{
    float max = tab[0];

    for(int i = 1; i<nbElements; i++)
    {
        if(tab[i] > tab[i-1])
        {
            max = tab[i];
        }
    }

    return max;
}