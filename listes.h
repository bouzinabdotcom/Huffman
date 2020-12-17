//TP2 liste TAD
#ifndef listes_H
#define listes_H
typedef struct zneoud * data;
//types
struct zmaillon {
	data el;
	struct zmaillon *suiv;
};

typedef struct zmaillon maillon;
typedef maillon * liste; //addresse du premier maillon

//prototypes
//constructeur
liste creer_liste_vide();
//observateur
int est_liste_vide(liste l);

//transformateurs
liste ajouter (data e, liste l);

data tete(liste l);

liste queue(liste l);

liste liberer_maillon(liste l);

void liberer_liste(liste l);

#endif