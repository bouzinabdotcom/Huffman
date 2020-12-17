//TP2 liste TAD
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "listes.h"

/*
//types
struct zmaillon {
	int el;
	struct maillon *suiv;
};

typedef struct zmaillon maillon;
typedef maillon * liste; //addresse du premier maillon
*/

//constructeur
liste creer_liste_vide(){
	return NULL;
}

//observateur
int est_liste_vide(liste l){
	return(l==NULL);
}

//transformateurs
liste ajouter (data e, liste l){ //ajoute un element e à la liste l
	//creer nouveau maillon
	maillon *temp;
	temp=(maillon*)malloc(sizeof(maillon));
	//attribution des elements du maillon
	temp->el=e;
	temp->suiv=l;
	return temp; //retourne addresse du nouveau maillon
}

data tete(liste l){ //renvoie le premier element de l
	assert(!est_liste_vide(l)); //si liste vide break
	return l->el;
}

liste queue(liste l){ //renvoie la suite de la liste
	assert(!est_liste_vide(l));
	return l->suiv;
}

liste liberer_maillon(liste l){
	assert (!est_liste_vide(l));
	maillon *tmp;
	tmp=l->suiv;
	free(l);
	return tmp;
}

void liberer_liste(liste l){
	if (est_liste_vide(l)) return;
	liberer_liste(queue(l));
	free(l);
}

	
/*	
//tests
int main(){
	liste l, l2;
	l=creer_liste_vide();
	printf("%d\n", est_liste_vide(l));
	l=ajouter(5,l);
	printf("%d\n", est_liste_vide(l));
	printf("%d\n", tete(l));
	l=ajouter(3,l);
	printf("%d\n", tete(l));
	l2=queue(l);
	printf("%d\n", tete(l2));
	afficher_liste(l);
	l=liberer_maillon(l);
	afficher_liste(l);
	liste l;
	liste x;
	l=creer_liste_vide();
	x=queue(l);
}
*/













