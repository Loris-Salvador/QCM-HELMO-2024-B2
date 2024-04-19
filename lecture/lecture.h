#ifndef Lecture_h
#define Lecture_h

/*--------------------------------------------------------------
Interface du module de lecture : lecture.h
---------------------------------------------------------------*/

/*--------------------------------------------------------------
Inviter � entrer une cha�ne de caract�res au clavier par le message
<invitation>, la lire et la ranger � partir de l'adresse <chaine> �
concurrence de <lgmax> caract�res ('\0' exclu) .
--------------------------------------------------------------*/
void LireChaine(char invitation[], int lgmax, char chaine[]);

/*--------------------------------------------------------------
Inviter � entrer un seul caract�re au clavier par le message
<invitation>, lire ce caract�re et le ranger � l'adresse <carac>
--------------------------------------------------------------*/
void LireCaractere(char invitation[], char *carac);

/*--------------------------------------------------------------
Inviter � entrer un caract�re en r�ponse � l'invitation <invitation>
Si le caract�re lu, ind�pendamment de la casse, est �gal � <affirmatif>,
la fonction retourne 1; s'il est �gal � <negatif> la fonction
retourne 0 sinon l'invitation � entrer un caract�re est �mise �
nouveau.
----------------------------------------------------------------*/
int Encore(char invitation[], char affirmatif, char negatif);

/*-------------------------------------------------------------------
Inviter � entrer un entier compris entre <binf> et <bsup>, au clavier
par le message <invitation>, le lire et le ranger � l'adresse <entier>
En cas d'erreur, la fonction retourne 0. La valeur point�e par
<entier> n'est significative que si la fonction retourne 1.
--------------------------------------------------------------------*/
int LireEntierEntre(char invitation[], int *entier, int binf, int bsup);

/*-----------------------------------------------------------------
Inviter � entrer un entier au clavier par le message <invitation>,
le lire et le ranger � l'adresse <entier>. En cas d'erreur, la fonction
retourne 0. La valeur point�e par <entier> n'est significative
que si la fonction retourne 1.
--------------------------------------------------------------------*/
int LireEntier(char invitation[], int *entier);

/*-------------------------------------------------------------------
Inviter � entrer un r�el compris entre <binf> et <bsup>, au clavier
par le message <invitation>, le lire et le ranger � l'adresse <entier>
En cas d'erreur, la fonction retourne 0. La valeur point�e par
<entier> n'est significative que si la fonction retourne 1.
--------------------------------------------------------------------*/
int LireReelEntre(char invitation[], float *reel, float binf, float bsup);

/*-------------------------------------------------------------------
Inviter � entrer un r�el au clavier par le message <invitation>,
le lire et le ranger � l'adresse <entier>. En cas d'erreur, la fonction
retourne 0. La valeur point�e par <entier> n'est significative
que si la fonction retourne 1.
--------------------------------------------------------------------*/
int LireReel(char invitation[], float *reel);


/*--------------------------------------------------------------
Inviter � entrer une chaine de caracteres au clavier par le message
<invitation>, la lire et la ranger dans un emplacement allou�
dynamiquement dont l'adresse sera la valeur de retour de la fonction.
Si l'allocation �choue, la valeur de retour vaut NULL. L'appelant doit lib�rer
l'emplacement.
--------------------------------------------------------------*/
char* LireChaineDynamique(char invitation[]);

#endif
