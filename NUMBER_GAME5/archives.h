#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#ifndef ARCHIVES_H_INCLUDED
#define ARCHIVES_H_INCLUDED

typedef struct {
    char *pseudo;
    int nbGenere;
    int *tentatives;
    char dateHeure[20];
    int nbTentative;
    float moyenne;
    float variance;
    float ecartType;
}Partie;

void recupererDateEtHeure(char *heure, int taille, Partie *p);
void enregistrerPartie(Partie *p);
void afficherHistorique(const char *pseudo);
void afficherStatistiques(const char *pseudo);

#endif // ARCHIVES_H_INCLUDED
