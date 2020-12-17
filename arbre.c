#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "arbre.h"
#include "listes.h"
#include "file.h"

// Type abstrait de données

arbre creer_arbre_vide (void)
{
  return NULL ;
}

arbre creer_arbre(Elt e, arbre fg, arbre fd)
{
  arbre nouveau;
  nouveau=(noeud*)malloc(sizeof(noeud));
  nouveau->elt=e;
  nouveau->fils_gauche=fg;
  nouveau->fils_droit=fd;
  return nouveau;
}

arbre fils_gauche(arbre a)
{
  assert(!est_arbre_vide(a));
  return a->fils_gauche;
}

arbre fils_droit(arbre a)
{
  assert(!est_arbre_vide(a));
  return a->fils_droit;
}

Elt racine(arbre a)
{
  assert(!est_arbre_vide(a));
  return a->elt;
}

bool est_arbre_vide(arbre a)
{
  return (a == NULL) ;
}

// Fonctions outils

arbre creer_feuille(Elt e)
{
  return creer_arbre(e, creer_arbre_vide(), creer_arbre_vide()) ;
}

bool est_feuille(arbre a)
{
  if (est_arbre_vide(a))
    return 0 ;
  return (est_arbre_vide(fils_gauche(a)) && est_arbre_vide(fils_droit(a))) ;
}

void print_arbre_aux(arbre a)
{
  if (est_arbre_vide(a))
    printf(".") ;
  else
  {
    if(racine(a).carac == 0) 
      printf("%d (", racine(a).count);
    else
      printf("%c (", racine(a).carac);

    print_arbre_aux(fils_gauche(a)) ;
    printf(") (");
    print_arbre_aux(fils_droit(a)) ;
    printf(")") ;
  }
}

void profondeur(arbre a, void action(arbre)){
  if(!est_arbre_vide(a)){
    profondeur(fils_gauche(a), action);
    profondeur(fils_droit(a), action);
    action(a);
  }
}

void largeur(arbre a, void action(arbre a)){
  file f;
  arbre tmp;
  assert(!est_arbre_vide(a));
  creer_file_vide(&f);
  enfiler(a,&f);
  while(!est_file_vide(f)){
    tmp=defiler(&f);
    action(tmp);
    if(!est_arbre_vide(fils_gauche(tmp))) enfiler(fils_gauche(tmp),&f);
    if(!est_arbre_vide(fils_droit(tmp))) enfiler(fils_droit(tmp),&f);
  }
}

void print_op(arbre(a)){
  if(est_arbre_vide(a)) printf(" ");
  else {
    if(racine(a).carac == 0) 
      printf("%d (", racine(a).count);
    else
      printf("%c (", racine(a).carac);
  }
}

void print_arbre(arbre a) // Notation préfixe
{
  print_arbre_aux(a) ;
  printf("\n") ;
}

void free_noeud(arbre a)
{
  free(a) ;
}

void free_arbre(arbre a)
{
  if(!est_arbre_vide(a)){
    free_arbre(fils_gauche(a));
    free_arbre(fils_droit(a));
    free(a);
  }
}

//fonction pour compter le nombre d'element d'un arbre
int nb_arbre(arbre a){
  if (est_arbre_vide(a)) return 0;
  return 1+nb_arbre(fils_gauche(a))+nb_arbre(fils_droit(a));
}

// void serialisation_rec(arbre a, char * serie, int * pi){ //serie string acceuillant le codage pi indice de serie
//   if (est_arbre_vide(a)) serie[(*pi)++]='0'; //cas arbre vide terminal
//   else { //cas arbre non vide
//     //mets dans la chaine "1+racine de a"
//     serie[(*pi)++]='1'; 
//     serie[(*pi)++]=racine(a).carac != 0 ? racine(a).carac : 7;
//     //appel recursif sur le fils droit et gauche
//     serialisation_rec(fils_gauche(a), serie, pi);
//     serialisation_rec(fils_droit(a), serie, pi);
//   }
// }

// char * serialisation(arbre a){ //fonction enrobage
//   //creer une chaine de char pour la serialisation
//   char * serie;
//   int i=0;
//   //taille de la chaine 2+nb_arbre(a)*3 car chaque element à 2 fils meme si ils sont vide
//   //2+ pour le premier '1'ou '0' et '\0'
//   serie=(char *)malloc((2+nb_arbre(a)*3)*sizeof(char));
//   serialisation_rec(a,serie,&i);
//   //ferme la chaine de char
//   serie[nb_arbre(a)*3+1]='\0';
//   return serie;
// }

// arbre deserialisation_rec(char * s, int * debut) {                                /*On crée une fonction recursive deserialisation prenant en argument un pointeur char s et un pointeur int qui pointera sur le début de la chaine s*/
//     arbre a ;                                                                     /*On crée un arbre a vide*/
//     a = creer_arbre_vide() ;
//     if(s[*debut] == '\0') return a;                                               /*Si le caractère à la position debut est '\0', on retourne a (Arbre vide)*/
//     if(s[*debut] == '1') {       
//         Data c;
//         c.carac = s[(*debut)+1] == 7 ? 0 : s[(*debut)+1];
//         c.count = 0;                                              /*Si le caractère à la position debut est '1'...*/
//         a = creer_arbre(c,creer_arbre_vide(),creer_arbre_vide()) ;    /*La racine de a, prend la valeur du caractère à la position debut + 1 (celui juste après le '1')*/
//         *debut = *debut + 2 ;                                                     /*On ajoute deux à l'entier debut afin qu'il pointe bien vers le caractère que l'on souhaite pour fils gauche*/
//         a->fils_gauche = deserialisation_rec(s,debut) ;                           /*On appelle la fonction pour traiter fils gauche et on fait la meme chose par la suite pour fils droit*/
//         *debut = *debut + 1 ;
//         a->fils_droit = deserialisation_rec(s,debut) ;
//     }
//     return a ;                                                                    /*On retourne l'arbre*/
// }

// arbre deserialisation(char * s) {                                                 /*On crée une fonction d'enrobage pour deserialisation_rec en initialisant debut à 0*/
//     int debut ;

//     debut = 0 ;
//     return deserialisation_rec(s,&debut) ;
// }

int serialisation_aux (arbre a, char * str, int i) {
  //cas terminaux
  if(est_arbre_vide(a)) {
    str[i] = '0';
    return i+1;
  }
  else {
    int i1, i2;
    str[i] = '1';
    str[i+1] = racine(a).carac == 0 ? 7 : racine(a).carac ;
    i1 = serialisation_aux(fils_gauche(a), str, i+2);
    i2 = serialisation_aux(fils_droit(a), str, i1);

    return i2;
  }

}

char * serialisation(arbre a) {
  int i;
  char * str = (char *)malloc((2+nb_arbre(a)*3)*sizeof(char));
  i = serialisation_aux(a, str, 0);
  str[i] = '\0';
  return str;
}

arbre deserialisation(char ** pstr) {
  arbre a1, a2;
  Data c;

  if((*pstr)[0]=='0') {
    *pstr = *pstr + 1;
    return creer_arbre_vide();
  }
  else {
    assert((*pstr)[0] == '1');
    
    c.carac = (*pstr)[1] == 7 ? 0 : (*pstr)[1];
    c.count = 0;


    *pstr = *pstr + 2;
    a1 = deserialisation(pstr);
    a2 = deserialisation(pstr);

    return creer_arbre(c, a1, a2);


  }
}