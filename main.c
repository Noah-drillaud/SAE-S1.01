#include <stdio.h>
#include <stdlib.h>

/** saisie utilisateur */

int lire_saisie(char *buffer, size_t taille)
{
    if (fgets(buffer, taille, stdin) == NULL)
    {
        return 0; // Erreur de lecture
    }
    buffer[strcspn(buffer, "\n")] = '\0'; // Supprimer le saut de ligne
    return 1;                             // Succès
}

int saisire_commande(char *buffer, size_t taille)
{
    while (1)
    {
        printf("Entrez une commande : ");
        if (!lire_saisie(buffer, taille))
        {
            return 0; // Erreur de lecture
        }
        if (strlen(buffer) > 0)
        {
            return 1; // Succès
        }
    }
}

int main()
{
    char saisie[100];
    
    while (saisire_commande(saisie, sizeof(saisie)))
    {
        printf("Vous avez saisi : %s\n", saisie);
    }
    return 0;
}