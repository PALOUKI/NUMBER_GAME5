/**

NOM         : ZANOU
PRENOM      :Félix Gbèdo
FILIER      :LP-GL
PROJET      : NUMBER_GAME
VERSION     : 5
FILE NAME   : ARCHIVE.C
BUT         : SAUVERGARDE DES DONNES STATISTIQUES

**/

#include "archives.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/**
FONCTION    : recupererDateEtHeure
AUTEUR      : ZANOU
BUT         : RECUPERER L'HEURE ET LA DATE
**/

void recupererDateEtHeure(char *heure, int taille, Partie *partie) {
    time_t temps = time(NULL);
    struct tm *tempsLocal = localtime(&temps);
    //Vérification de la récupération et de la conversion de la date
    if (temps == -1) {
        printf("Erreur lors de la récupération de l'heure\n");
    }else {
        if (tempsLocal == NULL) {
        printf("Erreur lors de la conversion de l'heure\n");
        }
        else
        {
            if (strftime(heure, taille, "%d-%m-%Y %H:%M:%S", tempsLocal) == 0){
            printf("Erreur lors du formatage de la date et de l'heure\n");
            }
        }
    }

    //Date et heure de la partie

    strncpy(partie->dateHeure, heure, taille);
    // S'assurer que la chaîne est terminée par un '\0'

    partie->dateHeure[taille - 1] = '\0';
}

/**
FONCTION    : enregistrerPartie
AUTEUR      : ZANOU
BUT         : ENREGISTRER LA PARTIE
**/

void enregistrerPartie(Partie *partie) {
    FILE *fichier = fopen("archive.cvs", "ab"); // Append pour ne pas écraser le fichier existant

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }else{
            fwrite(partie, sizeof(Partie), 1 , fichier);
        }
    fclose(fichier);
}

/**
FONCTION    : afficherHistorique
AUTEUR      : ZANOU
BUT         : AFFICHER HISTORIQUE
**/


void afficherHistorique(const char *pseudo) {
    int existance = 0;
    FILE* fichier = fopen("archive.cvs", "rb");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }else
        {
            Partie
            while (fread(&partie.pseudo, sizeof(char), strlen(partie.pseudo)+1, fichier) && strcmp(pseudo, partie.pseudo )==0) {
                printf("pseudo lu\n");
                existance += 1;
                fread(&partie.nbGenere, sizeof(int), 1, fichier);
                fread(&partie.nbTentative, sizeof(int), 1, fichier);
                partie.tentatives = malloc(partie.nbTentative * sizeof(int));
                    if (partie.tentatives == NULL) {
                        printf("Erreur d'allocation de mémoire\n");
                        fclose(fichier);
                    }
                    else
                    {
                        fread(partie.tentatives, sizeof(int), partie.nbTentative, fichier);
                    }
                    fread(partie.dateHeure, sizeof(char), 20, fichier);
                    fread(&partie.ecartType, sizeof(float), 1, fichier);

                    printf("---------------HISTORIQUE (partie %i)--------------------\n", existance);
                    printf("Date et Heure : %s\n", partie.dateHeure);
                    printf("Nombre mystérieux : %d\n", partie.nbGenere);
                    printf("Nombre de tentatives : %d\n", partie.nbTentative);

            for (int i = 0; i < partie.nbTentative; i++) {
                printf(" %d ", partie.tentatives[i]);
            }
            printf("------------------------------------------------\n");
            }
        fclose(fichier);
        if (existance == 0) {
        printf("Désolé, vous n'avez jamais joué à ce jeu\n");
        }
        else{
            printf("\n Nombre total de partie joué : %i", existance);
            }
        }
}


/**
FONCTION    : afficherStatistiques
AUTEUR      : ZANOU
BUT         : AFFICHE LES STATISTIQUES
**/


void afficherStatistiques(const char* pseudo) {
    int existance = 0;
    float Moyenne_globale = 0, variance_globale = 0, Ecartype_globale = 0;

    FILE *fichier = fopen("archive.cvs", "rb");

    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier\n");
    }else
        {
            Partie partie;

            while(fread(&partie.pseudo, sizeof(char), strlen(partie.pseudo)+1, fichier) > 0 && strcmp(pseudo, partie.pseudo) == 0) {
                existance += 1;
                /*fread(&partie.moyenne, sizeof(float), 1, fichier);
                fread(&partie.variance, sizeof(float), 1, fichier);
                fread(&partie.ecartType, sizeof(float), 1, fichier);*/

                Moyenne_globale += partie.moyenne;
                variance_globale += partie.variance;
                Ecartype_globale += partie.ecartType;

                printf("---------------Statistiques Partie %d--------------------\n",existance);
                printf("Moyenne %d   : %.2f\n",existance, partie.moyenne);
                printf("Variance %d  : %.2f\n", existance, partie.variance);
                printf("Ecart-Type %d: %.2f\n",existance,  partie.ecartType);
                printf("----------------------------------------------------------\n");
                }
             fclose(fichier);
            if (existance == 0) {
                printf("Désolé, vous n'avez jamais joué à ce jeu\n");
            } else {
                printf("---------------Statistiques Globales--------------------\n");
                printf("Moyenne Globale : %.2f\n", Moyenne_globale / existance);
                printf("Variance Globale : %.2f\n", variance_globale / existance);
                printf("Ecart-Type Global : %.2f\n", Ecartype_globale / existance);
                printf("Nombre total de partie joué : %i", existance);
                printf("---------------------------------------------------------\n");
            }
        }
}
