//TAD files
#ifndef file_H
#define file_H
#include "listes.h"
//type
struct zfile{
    maillon * premier;
    maillon * fin;
};
typedef struct zfile file;

//constructeur
void creer_file_vide(file * pfile);

//observateur
int est_file_vide(file file);

//transformateurs
void enfiler(data x, file * pfile);

data defiler(file * pfile);

#endif