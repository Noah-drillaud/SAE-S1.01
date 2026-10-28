#include <stdio.h>
#include <string.h>

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
    CMD_GAIN,
    CMD_SCORES,
    CMD_CLASSEMENT,
    CMD_COMPARAISON,
    CMD_BILAN,
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
    else if (strcmp(commande, "GAIN") == 0)
        return CMD_GAIN;
    else if (strcmp(commande, "SCORES") == 0)
        return CMD_SCORES;
    else if (strcmp(commande, "CLASSEMENT") == 0)
        return CMD_CLASSEMENT;
    else if (strcmp(commande, "COMPARAISON") == 0)
        return CMD_COMPARAISON;
    else if (strcmp(commande, "BILAN") == 0)
        return CMD_BILAN;
    else
        return CMD_INCONNU;
}

// Structure pour représenter un participant
typedef struct
{
    char nom[100];
    char prenom[100];
    int nb_concours_actifs;
    int scores[MAX_CONCOURS];
} Participant;

// Structure pour représenter un concours
typedef struct
{
    char nom[TAILLE_MAX];
    int nb_participants_actifs;
} Concours;

// structure pour représenter une ligne du classement
typedef struct
{
    int id_participant;
    int score;
} LigneClassement;

// Tableau principeaux
Participant les_participants[MAX_PARTICIPANTS];
int nb_participants = 0; // compteur du nombre de participants

Concours les_concours[MAX_CONCOURS];
int nb_concours = 0; // compteur du nombre de concours

// tableau pour stocker dernier position
int derniere_position[MAX_PARTICIPANTS][MAX_CONCOURS];

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
    for (int i = 0; i < nb_concours; i++)
    {
        les_participants[nb_participants].scores[i] = 0;
        derniere_position[nb_participants][i] = les_concours[i].nb_participants_actifs + 1;
    }

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

    // Rang de départ 1 pour tous les participants déjà inscrits
    for (int j = 0; j < nb_participants; j++)
    {
        les_participants[j].scores[nb_concours] = 0;
        derniere_position[j][nb_concours] = 1;
    }

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
        // Gestion du singulier/pluriel pour le mot "participant"
        if (les_concours[i].nb_participants_actifs <= 1)
        {
            printf("(%d) %s : %d participant\n",
                   i + 1, les_concours[i].nom, les_concours[i].nb_participants_actifs);
        }
        else
        {
            printf("(%d) %s : %d participants\n",
                   i + 1, les_concours[i].nom, les_concours[i].nb_participants_actifs);
        }
    }
}

// Fonction pour enregistrer le gain d'un participant dans un concours
void enregistrer_gain(int id_participant, int id_concours, int points)
{
    // conversion des identifiants en indices de tableau (-1)
    int indice_participant = id_participant - 1;
    int indice_concours = id_concours - 1;

    // Vérification du participant(si il existe)
    if (indice_participant < 0 || indice_participant >= nb_participants)
    {
        printf("Participant incorrect\n");
        return;
    }

    // Vérification du concours(si il existe)
    if (indice_concours < 0 || indice_concours >= nb_concours)
    {
        printf("Concours incorrect\n");
        return;
    }

    // Vérfication si les point sont corrects
    if (points <= 0)
    {
        printf("Points incorrects\n");
        return;
    }

    // Si c'est la première fois que le participant marque des points dans le concours, on incrémente le nombre de concours actifs pour ce participant
    if (les_participants[indice_participant].scores[indice_concours] == 0)
    {
        les_participants[indice_participant].nb_concours_actifs++;
        les_concours[indice_concours].nb_participants_actifs++;
    }

    // Enregistrement des points
    les_participants[indice_participant].scores[indice_concours] += points;

    printf("Gain enregistre\n");
}

// Fonction pour afficher le score d'un participant
void afficher_score(int id_participant)
{
    int indice_participant = id_participant - 1;

    // Vérification du participant(si il existe)
    if (indice_participant < 0 || indice_participant >= nb_participants)
    {
        printf("Identifiant incorrect\n");
        return;
    }

    // Affichage du nom et prénom du participant
    printf("%s %s\n", les_participants[indice_participant].prenom, les_participants[indice_participant].nom);

    if (les_participants[indice_participant].nb_concours_actifs == 0)
    {
        printf("Aucun gain\n");
        return;
    }

    // parcours des concours pour afficher les scores non nuls(trier par ID croissant)
    for (int concour = 0; concour < nb_concours; concour++)
    {
        if (les_participants[indice_participant].scores[concour] > 0)
        {
            int id_concours = concour + 1; // conversion de l'indice en ID
            int score = les_participants[indice_participant].scores[concour];

            // gestion du singulier/pluriel selon l'exemple du sujet ("1 point" vs "2 points")
            if (score == 1)
            {
                printf("(%d) %s : %d point\n", id_concours, les_concours[concour].nom, score);
            }
            else
            {
                printf("(%d) %s : %d points\n", id_concours, les_concours[concour].nom, score);
            }
        }
    }
}

// Fonction pour afficher le classement d'un concours
void afficher_classement(int id_concours)
{
    int indice_concours = id_concours - 1;

    // Vérification du concours(si il existe)
    if (indice_concours < 0 || indice_concours >= nb_concours)
    {
        printf("Identifiant incorrect\n");
        return;
    }

    // Vérification si le concours a des participants
    if (les_concours[indice_concours].nb_participants_actifs == 0)
    {
        printf("%s\n", les_concours[indice_concours].nom);
        printf("Aucun participant\n");
        return;
    }

    // affichage du nom du concours
    printf("%s\n", les_concours[indice_concours].nom);

    // tableau temporaire pour stocker les participants ayant des points
    LigneClassement classement[MAX_PARTICIPANTS];
    int nb_actifs = 0;

    for (int i = 0; i < nb_participants; i++)
    {
        if (les_participants[i].scores[indice_concours] > 0)
        {
            int score = les_participants[i].scores[indice_concours];
            if (score > 0)
            {
                classement[nb_actifs].id_participant = i + 1; // conversion de l'indice en ID
                classement[nb_actifs].score = score;
                nb_actifs++;
            }
        }
    }

    // tri du tableau classement par score décroissant
    for (int i = 0; i < nb_actifs - 1; i++)
    {
        for (int j = 0; j < nb_actifs - i - 1; j++)
        {
            if (classement[j].score < classement[j + 1].score ||
                (classement[j].score == classement[j + 1].score &&
                 classement[j].id_participant > classement[j + 1].id_participant))
            {
                LigneClassement temp = classement[j];
                classement[j] = classement[j + 1];
                classement[j + 1] = temp;
            }
        }
    }

    // affichage final avec gestion des ex aquo
    int position_reelle = 1;

    for (int i = 0; i < nb_actifs; i++)
    {
        int est_ex_aequo = 0;

        // Un participant est ex-aequo avec le précédent si son score est égal à celui du précédent ou du suivant
        if ((i > 0 && classement[i].score == classement[i - 1].score) ||
            (i < nb_actifs - 1 && classement[i].score == classement[i + 1].score))
        {
            est_ex_aequo = 1;
        }

        int index_p = classement[i].id_participant - 1;
        char *prenom = les_participants[index_p].prenom;
        char *nom = les_participants[index_p].nom;
        int score = classement[i].score;

        char *mot_point = (score == 1) ? "point" : "points";

        // Affichage
        if (est_ex_aequo)
        {
            printf("%dex -> (%d) %s %s : %d %s\n", position_reelle, classement[i].id_participant, prenom, nom, score, mot_point);
        }
        else
        {
            printf("%d -> (%d) %s %s : %d %s\n", position_reelle, classement[i].id_participant, prenom, nom, score, mot_point);
        }

        // On incémente la position réelle uniquement si le participant suivant a un score strictement inférieur
        if (i < nb_actifs - 1 && classement[i].score != classement[i + 1].score)
        {
            position_reelle = i + 2;
        }
    }
}

// Fonction pour comparer deux concours
void comparer_concours(int id_concours1, int id_concours2)
{
    int indice_concours1 = id_concours1 - 1;
    int indice_concours2 = id_concours2 - 1;

    // verifier si les concours existe
    if (indice_concours1 < 0 || indice_concours1 >= nb_concours ||
        indice_concours2 < 0 || indice_concours2 >= nb_concours)
    {
        printf("Identifiant incorrect\n");
        return;
    }

    // verifier s'il ya des participants avec des points dans les deux concours
    int total_participants_avec_points = 0;
    for (int i = 0; i < nb_participants; i++)
    {
        if (les_participants[i].scores[indice_concours1] > 0 || les_participants[i].scores[indice_concours2] > 0)
        {
            total_participants_avec_points++;
        }
    }

    // affichage des nom du concours
    printf("%s versus %s\n", les_concours[indice_concours2].nom, les_concours[indice_concours1].nom);

    if (total_participants_avec_points == 0)
    {
        printf("Aucun participant\n");
        return;
    }

    // verifier des concours incompatible
    for (int i = 0; i < nb_participants; i++)
    {
        if (les_participants[i].scores[indice_concours1] == 0 && les_participants[i].scores[indice_concours2] > 0)
        {
            printf("Concours incompatibles\n");
            return;
        }
    }

    // parcours tout les participants
    for (int i = 0; i < nb_participants; i++)
    {
        int score1 = les_participants[i].scores[indice_concours1];
        int score2 = les_participants[i].scores[indice_concours2];

        if (score1 > 0)
        {
            int id_p = i + 1;
            char *prenom = les_participants[i].prenom;
            char *nom = les_participants[i].nom;

            // calcul des pourcentage
            float pourcentage = ((float)score2 / (float)score1) * 100.0f;

            // gestion du singulier/pluriel
            char *mot_point1 = (score1 <= 1) ? "point" : "points";
            char *mot_point2 = (score2 <= 1) ? "point" : "points";

            printf("(%d) %s %s : %d %s/%d %s : %.2f%%\n",
                   id_p, prenom, nom,
                   score2, mot_point2,
                   score1, mot_point1,
                   pourcentage);
        }
    }
}

void afficher_bilan(int id_concours)
{
    int indice_concours = id_concours - 1;

    // verifier que le concours existe
    if (indice_concours < 0 || indice_concours >= nb_concours)
    {
        printf("Identifiant incorrect\n");
        return;
    }

    // affiche le nom du concours
    printf("%s\n", les_concours[indice_concours].nom);

    // verifier si il y a des participant avec des point
    if (les_concours[indice_concours].nb_participants_actifs == 0)
    {
        printf("Aucun participant\n");
        return;
    }

    // remplissage du tableau temporaire pour le trie
    LigneClassement classement[MAX_PARTICIPANTS];
    int nb_actifs = 0;

    for (int i = 0; i < nb_participants; i++)
    {
        int score = les_participants[i].scores[indice_concours];
        if (score > 0)
        {
            classement[nb_actifs].id_participant = i + 1;
            classement[nb_actifs].score = score;
            nb_actifs++;
        }
    }

    // tri (score décroissant et ID croissant)
    for (int i = 0; i < nb_actifs - 1; i++)
    {
        for (int j = 0; j < nb_actifs - i - 1; j++)
        {
            if (classement[j].score < classement[j + 1].score ||
                (classement[j].score == classement[j + 1].score && classement[j].id_participant > classement[j + 1].id_participant))
            {
                LigneClassement temp = classement[j];
                classement[j] = classement[j + 1];
                classement[j + 1] = temp;
            }
        }
    }

    // affichage du classement avec calcul du bien et perte de place
    int position_reelle = 1;

    for (int i = 0; i < nb_actifs; i++)
    {
        int est_ex_aequo = 0;
        if ((i > 0 && classement[i].score == classement[i - 1].score) ||
            (i < nb_actifs - 1 && classement[i].score == classement[i + 1].score))
        {
            est_ex_aequo = 1;
        }

        int idx_p = classement[i].id_participant - 1;
        char *prenom = les_participants[idx_p].prenom;
        char *nom = les_participants[idx_p].nom;
        int score = classement[i].score;
        char *mot_point = (score == 1) ? "point" : "points";

        // calcul de la variation des place
        int position_actuelle = position_reelle;
        int ancienne_position = derniere_position[idx_p][indice_concours];

        int diff = ancienne_position - position_actuelle;

        // memorisation de la position actuelle pour le prochain bilan
        derniere_position[idx_p][indice_concours] = position_actuelle;

        // formatage de l'affichage
        char variation_str[30];
        if (diff > 0)
        {
            if (diff == 1)
            {
                sprintf(variation_str, "+1 place");
            }
            else
            {
                sprintf(variation_str, "+%d places", diff);
            }
        }
        else if (diff < 0)
        {
            if (diff == -1)
            {
                sprintf(variation_str, "-1 place");
            }
            else
            {
                sprintf(variation_str, "%d places", diff);
            }
        }
        else
        {
            sprintf(variation_str, "+0 place");
        }

        // affichage de la ligne
        if (est_ex_aequo)
        {
            printf("%dex -> (%d) %s %s : %d %s : %s\n",
                   position_reelle, classement[i].id_participant, prenom, nom, score, mot_point, variation_str);
        }
        else
        {
            printf("%d -> (%d) %s %s : %d %s : %s\n",
                   position_reelle, classement[i].id_participant, prenom, nom, score, mot_point, variation_str);
        }

        // On incémente la position réelle uniquement si le participant suivant a un score strictement inférieur
        if (i < nb_actifs - 1 && classement[i].score != classement[i + 1].score)
        {
            position_reelle = i + 2;
        }
    }
}

// Fonction principale du programme
int main()
{
    char commande[50];

    for (int i = 0; i < MAX_PARTICIPANTS; i++)
    {
        for (int j = 0; j < MAX_CONCOURS; j++)
        {
            derniere_position[i][j] = -1;
        }
    }

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
        case CMD_GAIN:
        {
            int id_participant, id_concours, points;
            scanf("%d %d %d", &id_participant, &id_concours, &points);
            enregistrer_gain(id_participant, id_concours, points);
            break;
        }
        case CMD_SCORES:
        {
            int id_participant;
            scanf("%d", &id_participant);
            afficher_score(id_participant);
            break;
        }
        case CMD_CLASSEMENT:
        {
            int id_concours;
            scanf("%d", &id_concours);
            afficher_classement(id_concours);
            break;
        }
        case CMD_COMPARAISON:
        {
            int id_concours1, id_concours2;
            scanf("%d %d", &id_concours1, &id_concours2);
            comparer_concours(id_concours1, id_concours2);
            break;
        }
        case CMD_BILAN:
        {
            int id_concours;
            scanf("%d", &id_concours);
            afficher_bilan(id_concours);
            break;
        }
        // Ajouter les cas pour les autres commandes
        default:
            printf("Command not recognized.\n");
            break;
        }
    }

    return 0;
}