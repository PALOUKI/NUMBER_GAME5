/**

NOM         : ZANOU
PRENOM      :F�lix Gb�do
FILIER      :LP-GL
PROJET      : NUMBER_GAME
VERSION     : 5
FILE NAME   : JEU.C
BUT         : DEROULEMENT DU JEU

**/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "jeu.h"
#include "archives.h"



void jeu(Partie* partie) {
    int bornMax, nombreMaxTentative, choix;
    int nombreEntre, i, win=0;
    float moyenne = 0, variance = 0;
    char dateHeure[20];

    system("cls");
    printf("QUE LE JEU COMMENCE\n\n");

    do {
        printf("Choisissez votre niveau :\n");
        printf("\t 1. D�butant\n");
        printf("\t 2. Moyen\n");
        printf("\t 3. L�gende\n");
        printf("\t 4. Personnalis�\n");
        if (scanf("%d", &choix) != 1) {
            printf("Entr�e invalide, veuillez r�essayer.\n");
            while (getchar() != '\n'); // Vider le tampon
            choix = 0;
        }
    } while (choix < 1 || choix > 4);

    switch (choix) {
        case 1:
            bornMax = 100;
            nombreMaxTentative = 10;
            break;
        case 2:
            bornMax = 500;
            nombreMaxTentative = 20;
            break;
        case 3:
            bornMax = 2000;
            nombreMaxTentative = 25;
            break;
        case 4:
            do {
                printf("Entrez la borne maximale (>=10) : ");
                if (scanf("%d", &bornMax) != 1 || bornMax < 10) {
                    printf("Entr�e invalide, veuillez r�essayer.\n");
                    while (getchar() != '\n');
                    bornMax = 0;
                }
            } while (bornMax < 10);

            do {
                printf("Entrez le nombre de tentatives (>=10) : ");
                if (scanf("%d", &nombreMaxTentative) != 1 || nombreMaxTentative < 10) {
                    printf("Entr�e invalide, veuillez r�essayer.\n");
                    while (getchar() != '\n');
                    nombreMaxTentative = 0;
                }
            } while (nombreMaxTentative < 10);
    }

    partie->tentatives = malloc(sizeof(int) * nombreMaxTentative);
    srand(time(NULL));
    partie->nbGenere = rand() % bornMax + 1;

    printf("Le nombre myst�re est pr�t ! Vous pouvez commencer\n");
    i=0;
    while (i < nombreMaxTentative && win==0) {
        i++;
        printf("Devinez le nombre (%d/%d) : ", i, nombreMaxTentative);
        scanf("%d", &nombreEntre);
        moyenne+= nombreEntre;
        partie->tentatives[i-1]= nombreEntre;
        if (nombreEntre==partie->nbGenere)
        {
            win=1;
            if (i<=3)
            {
                printf("F�licitation vous avez trouv�! Vous �tes un super voyant.\n");
            }
            else if (i>=4 && i<=6)
            {
                printf("f�licitation vous avez trouv�! Vous �tes un sage voyant.\n");
            }
            else if (i>=7 && i<=9)
            {
                printf("F�licitations Vous avez trouv�! Vous �tes un apprenti voyant.\n");
            }
            else
            {
                printf("Humm enfin Vous avez trouv�! Vous �tes un voyant pusillanime.\n");
            }
        }
        else if (nombreEntre< partie->nbGenere)
        {
            printf("Oops! le nombre entr� est plus petit que le nombre myst�re. Ressayer!\n");
        }
        else
        {
            printf("Oops! Le nombre entr� est plus grand que le nombre � deviner. Ressayer!\n");
        }
        fflush(stdin);
        }
            if (i==nombreMaxTentative) {
            printf("GAME OVER ! Le nombre �tait %d.\n", partie->nbGenere);
            }

        moyenne /= i;
        partie->moyenne = moyenne;

        for (int j = 0; j < i; j++) {
            variance += pow(partie->tentatives[j] - moyenne, 2);
        }
        partie->variance = variance;
        partie->ecartType = sqrt(variance / i);
        partie->nbTentative = i;

        recupererDateEtHeure(dateHeure, sizeof(dateHeure), partie);
        enregistrerPartie(partie);
        free(partie->tentatives); // Lib�rer la m�moire allou�e
    }
