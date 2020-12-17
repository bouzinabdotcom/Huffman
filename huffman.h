#include "arbre.h"
#include "gestion_fichier.h"
#include <stdio.h>
#define NBASCII 256

typedef Data count;

count * comptage(char * chaine);
int nb_tab(count * T);
void tri_bulle(arbre * T,int N);
arbre * creer_tab_feuille(count * T, int N);
arbre codageHuff(arbre * T, int N);
int hauteur(arbre a);
void codage_char_rec(arbre a, char recherche, char code[], int h, int * trouve);
char * codage_char(arbre a, char recherche);
void codage_fichier(char * src, char * dest);
void decodage_fichier_aux(Bin_file * f, arbre a, arbre racine, FILE * out);
void decodage_fichier(char * src, char * dest);
