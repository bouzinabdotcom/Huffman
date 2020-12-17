//TAD files
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "file.h"
#include "listes.h"

//type
// struct zfile{
//     maillon* premier;
//     maillon* fin;
// };
// typedef struct zfile file;

//constructeur
void creer_file_vide(file * pfile){
    pfile->premier=NULL;
    pfile->fin=NULL;
}

//observateur
int est_file_vide(file file){
    return(file.premier==NULL);
}

//transformateurs
void enfiler(data x, file * pfile){
    maillon *nouveaux,*last;
    nouveaux=ajouter(x,creer_liste_vide());
    /*
    nouveaux=(maillon*)malloc(sizeof(maillon));
    nouveaux->el=x;
    nouveaux->suiv=NULL;
    */
    last=pfile->fin;
    if(last==NULL) pfile->premier=nouveaux; //file vide
    else last->suiv=nouveaux;
    pfile->fin=nouveaux;
}

data defiler(file * pfile){
    data x;
    maillon *m;
    assert(!est_file_vide(*pfile));
    m=pfile->premier;
    x=m->el;
    if(pfile->fin==m){ //file que d'un element
        pfile->premier=NULL;
        pfile->fin=NULL;
    }
    else pfile->premier=m->suiv;
    free(m);
    return x;
}

// int main(){
//     file f;
//     creer_file_vide(&f);
//     assert(est_file_vide(f));
//     enfiler(6,&f);
//     assert(!est_file_vide(f));
//     assert(defiler(&f)==6);
//     assert(est_file_vide(f));
//     printf("reussis\n");
// }