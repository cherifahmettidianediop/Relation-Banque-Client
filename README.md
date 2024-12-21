#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structures
 struct Client {
    char codeCL[10];
    char prenom[50];
    char nom[50];
    char telephone[15];
    char filiere[50];
    struct Client *next;
} 

 struct Compte {
    char numeroCompte[10];
    char dateOuverture[20];
    char agence[50];
    char codeCL[10];
    float solde;
    struct Compte *next;
} 

 struct Operation {
    char codeOp[10];
    char numeroCompte[10];
    char type[10];
    float montant;
    char date[20];
    struct Operation *next;
} Operation;