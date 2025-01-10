#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include "pseudo.h"
#include "jeu.h"
#include "archives.h"

int main() {
    Partie* p = (Partie*)malloc(sizeof(Partie));
    int choix;
    char outOrContinuPartie, quitterDefinitevement = 'N';

    // Début du programme

    setlocale(LC_CTYPE, "");

    // gerer le pseudo

    gererPseudo(p);

    do {
        printf("\n------------------- MENU -------------------\n");
        printf("\t 1. Nouvelle partie\n");
        printf("\t 2. Consulter les archives\n");
        printf("\t 3. Voir les statistiques\n");
        printf("\t 4. Quitter le jeu\n");
        printf("-------------------------------------------\n");
        printf("Entrez votre choix : ");
        scanf("%i", &choix);

        switch (choix) {
        case 1:
            do {
                // Lancer une nouvelle partie
                jeu(p);
                free(p);
                printf("\nVoulez-vous reprendre une autre partie ? (O/N) : ");
                scanf(" %c", &outOrContinuPartie);
            } while (outOrContinuPartie != 'N');
            break;

        case 2:
            // Afficher l'historique
            afficherHistorique(p->pseudo);
            break;

        case 3:
            // Afficher les statistiques
            afficherStatistiques(p->pseudo);
            break;

        case 4:
            // Quitter le jeu
            printf("Merci d'avoir joué ! À bientôt.\n");
            quitterDefinitevement = 'O';
            break;
        }
    } while (quitterDefinitevement == 'N'); // Répéter tant que l'utilisateur ne souhaite pas quitter

    // Libérer la mémoire allouée pour le pseudo
    if (p->pseudo != NULL) {
        free(p->pseudo);
    }
    free(p);

    return 0;
}
