#include "pseudo.h"
#include "archives.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void gererPseudo(Partie *p) {
    FILE *fichier;
    char nouveau[4];
    char pseudo[50];
    char verfPseudo[50];
    int pseudoExiste = 0;

    system("cls");
    printf("-------------------WELCOME TO THE NUMBER GAME-------------------\n");
    do {
        printf("Est-ce votre première fois de jouer à ce jeu ? (OUI/NON)\n");
        fgets(nouveau, sizeof(nouveau), stdin);
        nouveau[strcspn(nouveau, "\n")] = '\0';
        fflush(stdin);
    } while (strcmp(nouveau, "OUI") != 0 && strcmp(nouveau, "NON") != 0);

    do {
        printf("Veuillez entrer votre pseudo\n");
        fgets(pseudo, sizeof(pseudo), stdin);
        pseudo[strcspn(pseudo, "\n")] = '\0';
        fflush(stdin);

        fichier = fopen("Data.txt", "r");

        if (fichier == NULL) {
            fichier = fopen("Data.txt", "a");
            if (fichier == NULL) {
                printf("Erreur lors de l'ouverture du fichier\n");
            }
        } else {
            pseudoExiste = 0;
            while (fgets(verfPseudo, sizeof(verfPseudo), fichier)&& pseudoExiste==0) {
                verfPseudo[strcspn(verfPseudo, "\n")] = '\0';
                if (strcmp(pseudo, verfPseudo) == 0) {
                    pseudoExiste = 1;
                }
            }
        }

        fclose(fichier);

        if (strcmp(nouveau, "OUI") == 0) {
            if (pseudoExiste) {
                printf("Ce pseudo existe déjà ! Veuillez en entrer un autre.\n");
                pseudoExiste=0;
            } else {
                printf("Bienvenu dans notre sublime jeu %s", pseudo);
                fichier = fopen("Data.txt", "a");
                fprintf(fichier, "%s\n", pseudo);
                fclose(fichier);
                pseudoExiste=1;
            }
        } else if (strcmp(nouveau, "NON") == 0) {
            if (pseudoExiste) {
                printf("Ravi de vous revoir, %s !\n", pseudo);
            } else {
                printf("Pseudo inconnu ! Veuillez réessayer.\n");
            }
        }
    } while (pseudoExiste==0);

    p->pseudo = malloc(strlen(pseudo) + 1);
    strcpy(p->pseudo, pseudo);
}
