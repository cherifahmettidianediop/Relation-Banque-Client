#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structures
typedef struct Client {
    char codecli[20]; 
    char prenom[50];
    char nom[50];
    char tel[15];
    char ville[50];
    struct Client* suivant;
} Client;

typedef struct Compte {
    int numero;
    char dateOuverture[11];
    char agence[50];
    float solde;
    char codecli[20]; 
    struct Compte* suivant;
} Compte;

typedef struct Operation {
    int numeroCompte;
    char type[10]; 
    float montant;
    char dateOp[11];
    struct Operation* suivant;
} Operation;

// Prototypes des fonctions
Client* ajouterClient(Client* tete);
void afficherClients(Client* tete);
Compte* creerCompte(Compte* tete, Client* clients);
void afficherComptes(Compte* tete);
Operation* effectuerOperation(Operation* tete, Compte* comptes);
void afficherOperations(Operation* tete);
int verifierClient(Client* tete, char codecli[]);
void menu(Client** listeClients, Compte** listeComptes, Operation** listeOperations);

int main() {
    Client* listeClients = NULL;    
    Compte* listeComptes = NULL;   
    Operation* listeOperations = NULL;

// Affichage du menu principal
    menu(&listeClients, &listeComptes, &listeOperations);

    return 0;
}

// Fonction pour ajouter un client
Client* ajouterClient(Client* tete) {
    Client* nouveau = (Client*)malloc(sizeof(Client));

    printf("Code client : ");
    scanf("%s", nouveau->codecli);

    // Vérifier si le client existe déjà
    if (verifierClient(tete, nouveau->codecli)) {
        printf("Un client avec ce code existe deja !\n");
        free(nouveau);
        return tete;
    }

    printf("Prenom : ");
    scanf("%s", nouveau->prenom);
    printf("Nom : ");
    scanf("%s", nouveau->nom);
    printf("Telephone : ");
    scanf("%s", nouveau->tel);
    printf("Ville : ");
    scanf("%s", nouveau->ville);

    nouveau->suivant = tete;

    // Sauvegarder dans un fichier
    FILE* fichier = fopen("clients.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "%s %s %s %s %s\n", nouveau->codecli, nouveau->prenom, nouveau->nom, nouveau->tel, nouveau->ville);
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier clients.txt\n");
    }

    printf("Client ajoute avec succes.\n");
    return nouveau;
}

// Fonction pour vérifier si un client existe
int verifierClient(Client* tete, char codecli[]) {
    while (tete != NULL) {
        if (strcmp(tete->codecli, codecli) == 0) {
            return 1; 
        }
        tete = tete->suivant;
    }
    return 0; 
}

// Fonction pour afficher tous les clients
void afficherClients(Client* tete) {
    if (tete == NULL) {
        printf("Aucun client enregistre.\n");
        return;
    }

    printf("\n--- Liste des Clients ---\n");
    Client* courant = tete;
    while (courant != NULL) {
        printf("Code : %s, Prénom : %s, Nom : %s, Téléphone : %s, Ville : %s\n",
               courant->codecli, courant->prenom, courant->nom, courant->tel, courant->ville);
        courant = courant->suivant;
    }
}

// Fonction pour créer un compte
Compte* creerCompte(Compte* tete, Client* clients) {
    Compte* nouveau = (Compte*)malloc(sizeof(Compte));

    printf("Code client pour le compte : ");
    scanf("%s", nouveau->codecli);

    // Vérifier si le client existe
    if (!verifierClient(clients, nouveau->codecli)) {
        printf("Le client avec ce code n'existe pas !\n");
        free(nouveau);
        return tete;
    }

    printf("Numero de compte : ");
    scanf("%d", &nouveau->numero);
    printf("Date d'ouverture (JJ/MM/AAAA) : ");
    scanf("%s", nouveau->dateOuverture);
    printf("Agence : ");
    scanf("%s", nouveau->agence);
    nouveau->solde = 0.0;

    nouveau->suivant = tete;

    // Sauvegarder dans un fichier
    FILE* fichier = fopen("comptes.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "%d %s %s %.2f %s\n", nouveau->numero, nouveau->dateOuverture, nouveau->agence, nouveau->solde, nouveau->codecli);
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier comptes.txt\n");
    }

    printf("Compte cree avec succes.\n");
    return nouveau;
}

// Fonction pour afficher tous les comptes
void afficherComptes(Compte* tete) {
    if (tete == NULL) {
        printf("Aucun compte enregistre.\n");
        return;
    }

    printf("\n--- Liste des Comptes ---\n");
    Compte* courant = tete;
    while (courant != NULL) {
        printf("Numero : %d, Date : %s, Agence : %s, Solde : %.2f, Code Client : %s\n",
               courant->numero, courant->dateOuverture, courant->agence, courant->solde, courant->codecli);
        courant = courant->suivant;
    }
}

// Fonction pour effectuer une opération
Operation* effectuerOperation(Operation* tete, Compte* comptes) {
    int numeroCompte;
    char type[10];
    float montant;
    char dateOp[11];

    printf("Numero de compte : ");
    scanf("%d", &numeroCompte);

    // Vérifier si le compte existe
    Compte* courant = comptes;
    while (courant != NULL && courant->numero != numeroCompte) {
        courant = courant->suivant;
    }
    if (courant == NULL) {
        printf("Compte introuvable.\n");
        return tete;
    }

    printf("Type d'opération (dépôt/retrait) : ");
    scanf("%s", type);
    printf("Montant : ");
    scanf("%f", &montant);
    printf("Date (JJ/MM/AAAA) : ");
    scanf("%s", dateOp);

    // Vérification et mise à jour du solde
    if (strcmp(type, "retrait") == 0 && courant->solde < montant) {
        printf("Fonds insuffisants.\n");
        return tete;
    }
    if (strcmp(type, "depot") == 0) {
        courant->solde += montant;
    } else {
        courant->solde -= montant;
    }

    // Enregistrer l'opération
    Operation* nouvelle = (Operation*)malloc(sizeof(Operation));
    nouvelle->numeroCompte = numeroCompte;
    strcpy(nouvelle->type, type);
    nouvelle->montant = montant;
    strcpy(nouvelle->dateOp, dateOp);
    nouvelle->suivant = tete;

    FILE* fichier = fopen("operations.txt", "a");
    if (fichier != NULL) {
        fprintf(fichier, "%d %s %.2f %s\n", numeroCompte, type, montant, dateOp);
        fclose(fichier);
    } else {
        printf("Erreur lors de l'ouverture du fichier operations.txt\n");
    }

    printf("Operation effectuee avec succes.\n");
    return nouvelle;
}

// Fonction pour afficher toutes les opérations
void afficherOperations(Operation* tete) {
    if (tete == NULL) {
        printf("Aucune operation enregistree.\n");
        return;
    }

    printf("\n--- Liste des Opérations ---\n");
    Operation* courant = tete;
    while (courant != NULL) {²
        printf("Compte : %d, Type : %s, Montant : %.2f, Date : %s\n",
               courant->numeroCompte, courant->type, courant->montant, courant->dateOp);
        courant = courant->suivant;
    }
}

// Fonction pour afficher le menu principal
void menu(Client** listeClients, Compte** listeComptes, Operation** listeOperations) {
    int choix;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Gestion des clients\n");
        printf("2. Gestion des comptes\n");
        printf("3. Gestion des operations\n");
        printf("4. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                printf("\n1. Ajouter un client\n2. Afficher les clients\nVotre choix : ");
                int choixClient;
                scanf("%d", &choixClient);
                if (choixClient == 1) {
                    *listeClients = ajouterClient(*listeClients);
                } else if (choixClient == 2) {
                    afficherClients(*listeClients);
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            case 2:
                printf("\n1. Créer un compte\n2. Afficher les comptes\nVotre choix : ");
                int choixCompte;
                scanf("%d", &choixCompte);
                if (choixCompte == 1) {
                    *listeComptes = creerCompte(*listeComptes, *listeClients);
                } else if (choixCompte == 2) {
                    afficherComptes(*listeComptes);
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            case 3:
                printf("\n1. Effectuer une opération\n2. Afficher les opérations\nVotre choix : ");
                int choixOperation;
                scanf("%d", &choixOperation);
                if (choixOperation == 1) {
                    *listeOperations = effectuerOperation(*listeOperations, *listeComptes);
                } else if (choixOperation == 2) {
                    afficherOperations(*listeOperations);
                } else {
                    printf("Choix invalide.\n");
                }
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 4);
} 
// modification du fichier
int add(int a, int b){
    return a+b;
}
// modification du fichier
int add(int a, int b){
    return a+b;
}