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
    // Fonction pour générer un code unique
string generer_code(const string& prefix) {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 15);

    stringstream code;
    code << prefix << "-";
    for (int i = 0; i < 8; ++i) {
        int val = dis(gen);
        code << hex << uppercase << val;
    }
    return code.str();
}

/// Fonctions pour écrire dans un fichier
void sauvegarder_clients(const vector<Client>& clients) {
    ofstream fichier("clients.txt");
    for (const auto& client : clients) {
        fichier << client.code << ";" << client.prenom << ";" << client.nom << ";"
                << client.tel << ";" << client.ville << endl;
    }
    fichier.close();
}

void sauvegarder_comptes(const vector<Compte>& comptes) {
    ofstream fichier("comptes.txt");
    for (const auto& compte : comptes) {
        fichier << compte.numero << ";" << compte.dateOuverture << ";" << compte.agence
                << ";" << compte.solde << ";" << compte.codeClient << endl;
    }
    fichier.close();
}
void sauvegarder_operations(const vector<Operation>& operations) {
    ofstream fichier("operations.txt");
    for (const auto& operation : operations) {
        fichier << operation.code << ";" << operation.numeroCompte << ";" << operation.typeOp
                << ";" << operation.montant << ";" << operation.dateOperation << endl;
    }
    fichier.close();
}

// Fonctions pour lire depuis un fichier
void charger_clients(vector<Client>& clients) {
    ifstream fichier("clients.txt");
    if (!fichier.is_open()) return;
 string ligne;
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string code, prenom, nom, tel, ville;
        getline(ss, code, ';');
        getline(ss, prenom, ';');
        getline(ss, nom, ';');
        getline(ss, tel, ';');
        getline(ss, ville, ';');
        clients.push_back({code, prenom, nom, tel, ville});
    }
    fichier.close();
}

void charger_comptes(vector<Compte>& comptes) {
    ifstream fichier("comptes.txt");
    if (!fichier.is_open()) return;

    string ligne;
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string numero, dateOuverture, agence, codeClient;
        double solde;
        getline(ss, numero, ';');
        getline(ss, dateOuverture, ';');
        getline(ss, agence, ';');
        ss >> solde;
        ss.ignore();
        getline(ss, codeClient, ';');
        comptes.push_back({numero, dateOuverture, agence, solde, codeClient});
    }
    fichier.close();
}
void charger_operations(vector<Operation>& operations) {
    ifstream fichier("operations.txt");
    if (!fichier.is_open()) return;

    string ligne;
    while (getline(fichier, ligne)) {
        stringstream ss(ligne);
        string code, numeroCompte, typeOp, dateOperation;
        double montant;
        getline(ss, code, ';');
        getline(ss, numeroCompte, ';');
        getline(ss, typeOp, ';');
        ss >> montant;
        ss.ignore();
        getline(ss, dateOperation, ';');
        operations.push_back({code, numeroCompte, typeOp, montant, dateOperation});
    }
    fichier.close();
}
