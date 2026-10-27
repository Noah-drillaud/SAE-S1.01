#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PARTICIPANTS 100
#define MAX_CONCOURS 20
#define TAILLE_MAX 31 // 30 caractères +1 pour marquer la fin de la chaîne

// Définition des types de commandes
typedef enum
{
    CMD_EXIT,
    CMD_INSCRIRE,
    CMD_PARTICIPANTS,
    CMD_CREER,
    CMD_CONCOURS,
    CMD_INCONNU,
} TypeCommande;

// Fonction pour identifier la commande entrée par l'utilisateur
TypeCommande identifier_commande(const char *commande)
{
    if (strcmp(commande, "EXIT") == 0)
        return CMD_EXIT;
    else if (strcmp(commande, "INSCRIRE") == 0)
        return CMD_INSCRIRE;
    else if (strcmp(commande, "PARTICIPANTS") == 0)
        return CMD_PARTICIPANTS;
    else if (strcmp(commande, "CREER") == 0)
        return CMD_CREER;
    else if (strcmp(commande, "CONCOURS") == 0)
        return CMD_CONCOURS;
    else
        return CMD_INCONNU;
}

// Structure pour représenter un participant
typedef struct
{
    char nom[100];
    char prenom[100];
    int nb_concours_actifs;
} Participant;

// Structure pour représenter un concours
typedef struct
{
    char nom[TAILLE_MAX];
    int nb_participants_actifs;
} Concours;

// Tableau principeaux
Participant les_participants[MAX_PARTICIPANTS];
int nb_participants = 0; // compteur du nombre de participants

Concours les_concours[MAX_CONCOURS];
int nb_concours = 0; // compteur du nombre de concours

// Fonction pour inscrire un participant
void inscrire_participant(const char *prenom, const char *nom)
{
    // Vérifier si le participant existe déjà
    for (int i = 0; i < nb_participants; i++)
    {
        if (strcmp(les_participants[i].prenom, prenom) == 0 &&
            strcmp(les_participants[i].nom, nom) == 0)
        {
            printf("Nom incorrect\n");
            return;
        }
    }

    // Vérifier si le nombre maximum de participants est atteint
    if (nb_participants >= MAX_PARTICIPANTS)
    {
        printf("Nombre maximum de participants atteint.\n");
        return;
    }

    // Ajouter le participant
    strcpy(les_participants[nb_participants].prenom, prenom);
    strcpy(les_participants[nb_participants].nom, nom);
    les_participants[nb_participants].nb_concours_actifs = 0;

    nb_participants++;

    printf("Inscription enregistree (%d)\n", nb_participants);
}

// Fonction pour afficher la liste des participants
void afficher_participants()
{
    if (nb_participants == 0)
    {
        printf("Aucun participant inscrit\n");
        return;
    }
    for (int i = 0; i < nb_participants; i++)
    {
        printf("(%d) %s %s : %d concours\n",
               i + 1,
               les_participants[i].prenom,
               les_participants[i].nom,
               les_participants[i].nb_concours_actifs);
    }
}

// Fonction pour créer un concours
void creer_concours(const char *nom_concours)
{
    // Vérifier si le concours existe déjà
    for (int i = 0; i < nb_concours; i++)
    {
        if (strcmp(les_concours[i].nom, nom_concours) == 0)
        {
            printf("Nom incorrect\n");
            return;
        }
    }

    // Vérifier si le nombre maximum de concours est atteint
    if (nb_concours >= MAX_CONCOURS)
    {
        printf("Nombre maximum de concours atteint.\n");
        return;
    }

    // Ajouter le concours
    strcpy(les_concours[nb_concours].nom, nom_concours);
    les_concours[nb_concours].nb_participants_actifs = 0;

    nb_concours++;

    printf("Creation enregistree (%d)\n", nb_concours);
}

// Fonction pour afficher la liste des concours
void afficher_concours()
{
    if (nb_concours == 0)
    {
        printf("Aucun concours cree\n");
        return;
    }
    for (int i = 0; i < nb_concours; i++)
    {
        printf("(%d) %s : %d participant\n",
               i + 1, les_concours[i].nom, les_concours[i].nb_participants_actifs);
    }
}
int main()
{
    char commande[50];

    // boucle principale du programme
    while (1)
    {
        if (scanf("%s", commande) != 1)
        {
            break; // Sortir de la boucle si la lecture échoue
        }

        switch (identifier_commande(commande))
        {
        case CMD_EXIT:
            return 0;
        case CMD_INSCRIRE:
        {
            char nom[TAILLE_MAX], prenom[TAILLE_MAX];
            scanf("%s %s", prenom, nom);
            inscrire_participant(prenom, nom);
            break;
        }
        case CMD_PARTICIPANTS:
            afficher_participants();
            break;
        case CMD_CREER:
        {
            char nom_concours[TAILLE_MAX];
            scanf("%s", nom_concours);
            creer_concours(nom_concours);
            break;
        }
        case CMD_CONCOURS:
            afficher_concours();
            break;
        // Ajouter les cas pour les autres commandes
        default:
            printf("Command not recognized.\n");
            break;
        }
    }

    return 0;
}