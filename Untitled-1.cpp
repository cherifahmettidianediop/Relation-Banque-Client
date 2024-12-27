#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
// fonction
Client* ajouterClient(Client* tete) {
    Client* new = (Client*)malloc(sizeof(Client));
    printf("Code client : ");
    scanf("%s", new->codecli);
    printf("Prénom : ");
    scanf("%s", new->prenom);
    printf("Nom : ");
    scanf("%s", new->nom);
    printf("Téléphone : ");
    scanf("%s", new->tel);
    printf("Ville : ");
    scanf("%s", new->ville);
    new->next = tete;

    //Menu Principal 
   void menu() {
    int choix;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Gestion des clients\n");
        printf("2. Gestion des comptes\n");
        printf("3. Gestion des opérations\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // Consommer le caractère de nouvelle ligne

        switch (choix) {
            case 1:
                printf("\n1. Ajouter un client\n2. Afficher les clients\nVotre choix : ");
                int choixClient;
                scanf("%d", &choixClient);
                getchar();
                if (choixClient == 1) enregistrerClient();
                else if (choixClient == 2) afficherClients();
                else printf("Choix invalide !\n");
                break;
            case 2:
                printf("\n1. Créer un compte\n2. Afficher les comptes\nVotre choix : ");
                int choixCompte;
                scanf("%d", &choixCompte);
                getchar();
                if (choixCompte == 1) creerCompte();
                else if (choixCompte == 2) afficherComptes();
                else printf("Choix invalide !\n");
                break;
            case 3:
                printf("\n1. Effectuer une opération\n2. Afficher les opérations\nVotre choix : ");
                int choixOperation;
                scanf("%d", &choixOperation);
                getchar();
                if (choixOperation == 1) effectuerOperation();
                else if (choixOperation == 2) afficherOperations();
                else printf("Choix invalide !\n");
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide !\n");
        }
    } while (choix != 4);
}

int main() {
