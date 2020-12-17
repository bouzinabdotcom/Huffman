#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "huffman.h"







//compte le nombre d'occurences de characteres dans une chaine et cree un tableau de structures count
count * comptage(char * chaine){
    count * tab;
    //i indice de chaine j indice de fin de tab c indice de tab trouver bool
    int i=0, j=0, c, trouver;
    //suppose qu'il n'y aura pas plus de 128 char differents
    tab=(count*)malloc(NBASCII*sizeof(count)); 
    //tant que non fin de chaine 
    while(chaine[i]!='\0'){
        trouver=0;
        c=0;
        //tant que fin de tab non atteinte
        while(c<j && trouver==0){
            //cherche si char est déjà dans le tab
            if(chaine[i]==((tab[c]).carac)) trouver=1;
            else c++;
        }
        //char dans tab
        if(trouver==1) (tab[c]).count++;
        //nouveaux char
        else {
            (tab[j]).carac=chaine[i];
            (tab[j]).count=1;
            j++;
        }
        i++;
    }
    //indique fin tab
    (tab[j]).carac = 3;
    (tab[j]).count=1;
    (tab[j+1]).count=0;
    return tab;
}



//compte le nombre de data dans T
int nb_tab(count * T){
    int i=0;
    while(T[i].count!=0){
        i++;
    }
    return i;
}

void tri_bulle(arbre * T,int N){
	int j=0,k;
    arbre temp;
	int trie;/*agit comme un bool 0=false 1=true*/
	do {
		trie=1;
		k=j;
		for (int i=N-2;i>=k;i=i-1){
			if ((T[i]->elt).count>(T[i+1]->elt).count){
				temp=T[i];
				T[i]=T[i+1];
				T[i+1]=temp;
				j=i;
				trie=0;

			}
		}
	}while (trie==0);
}

//creer un tableau de feuille
arbre * creer_tab_feuille(count * T, int N){
    //tableau de feuille aussi grand que T
    // int j=nb_tab(T);
    //creer tableau d'arbre
    arbre * tabHuff;
    tabHuff=(arbre*)malloc(N*sizeof(arbre));
    //ceer les feuilles
    for(int i=0; i<N; i++){
        tabHuff[i]=creer_feuille(T[i]);
    }
    //libère mémoire T soucie de mémoire
    free(T);
    //retourne le tableau
    return tabHuff;
}

//creer un arbre de Huffman
arbre codageHuff(arbre * T, int N){
    //entier nb nombre de récurence
    int nb;
    Data racine;
    while(N>1){
        //tri car bulle car que un seul element à trié
        tri_bulle(T,N);
        //récurrence dans la racine
        nb=(T[0]->elt).count+(T[1]->elt).count;
        //creer un arbre avec les 2 premier el (le place en premier)
        racine.count=nb;
        racine.carac=0;

        T[0]=creer_arbre(racine,T[0],T[1]);
        //décalage des éléments à gauche
        for(int i=1; i<N-1; i++){
            T[i]=T[i+1];
        }
        //décrémente taille tableaux
        N--;
    }
    //retourne arbre
    return T[0];
}



int hauteur(arbre a){
  //cas terminal
  if (est_arbre_vide(a)) return 0;
  else
  {
    int h1, h2;
    h1=hauteur(fils_gauche(a));
    h2=hauteur(fils_droit(a));
    //renvoie hauteur max + 1
    if(h1>h2) return 1+h1;
    else return 1+h2;
  }
  
}

void codage_char_rec(arbre a, char recherche, char code[], int h, int * trouve){
    
    if(!*trouve){
        if(est_feuille(a) && racine(a).carac==recherche){
            code[h]='\0';
            *trouve = 1;
            //if(est_feuille(a)) printf("%d - %c - %c\n", *trouve, racine(a).carac, recherche);
            //puts(code);
        }
        else if(!est_arbre_vide(a)){
            code[h]='0';
            codage_char_rec(fils_gauche(a),recherche,code,h+1, trouve);
            if(!*trouve){
                code[h]='1';
                codage_char_rec(fils_droit(a),recherche,code,h+1, trouve);
            }
        }
    }

    


}



char * codage_char(arbre a, char recherche){
    char * code = calloc(hauteur(a), sizeof(char));
    int trouve = 0;
    codage_char_rec(a, recherche, code, 0, &trouve);
    return code;
}

//prend un fichier en entrée 
void codage_fichier(char * src, char * dest) {
    //lire une chaine du fichier src
    char * str = fichier_to_str(src);
    //creer un arbre de codage
    count * tab = NULL;
    tab = comptage(str);
    int nbtab = nb_tab(tab);
    arbre huff = codageHuff(creer_tab_feuille(tab, nbtab), nbtab);
    //ecrire l'arbre en binaire sur le fichier dest
    char * serie = serialisation(huff);
    Bin_file * d = openf(dest, 'w');
    if(d == NULL){
        puts("Erreur de lecture de fichier.");
        exit(EXIT_FAILURE);
    }

    unsigned int len = strlen(serie);
    //printf("%d\n", len);
    fwrite(&len, 1, sizeof(unsigned int), d->file);

    // fseek(out, -sizeof(unsigned int), SEEK_CUR);
    // unsigned int rlen = 0;
    // fread(&rlen, 1, sizeof(unsigned int), out);

    // printf("-rlen = %d\n", rlen);

    fwrite(serie, 1, len, d->file);
    //fclose(out);

    //coder chaque caractere et l'ecrire bit a bit dans notre fichier dest
    
    
    char * code = NULL;

    while(*str != '\0') {
        code = codage_char(huff, *str);
        while(*code != '\0'){
            write_b(d, *code);
            code++;

        }
        str++;
    }


    //ajouter le code du caractere de fin de fichier 
    char * fin = codage_char(huff, 3);
    while(*fin != '\0'){
        write_b(d, *fin);

        fin++;    
    }
    //done.
    
    closef(d);
    
    // fseek(out, 0, SEEK_SET);
    // unsigned int rlen = 0;
    // fread(&rlen, 1, sizeof(unsigned int), out);

    // printf("-rlen = %d\n", rlen);


}

void decodage_fichier_aux(Bin_file * f, arbre a, arbre racine, FILE * out) {
    assert(!est_arbre_vide(a));
    if(est_feuille(a)) {
        if(a->elt.carac == 3) {
            return; 
        }
        fprintf(out, "%c", a->elt.carac);
        decodage_fichier_aux(f, racine, racine, out);
    }
    else {
        if(read_b(f) == '1') decodage_fichier_aux(f, fils_droit(a), racine, out);
        else decodage_fichier_aux(f, fils_gauche(a), racine, out);
    }
}

//fonction qui decode un fichier
void decodage_fichier(char * src, char * dest) {
    //lire la taille de la chaine "arbre serialisé"
    unsigned int serieslen = 6;
    Bin_file * fich = openf(src, 'r');

    if(fich==NULL) {
        puts("Erreur de lecture de fichier.");
        exit(EXIT_FAILURE);
    }
    fread(&serieslen, 1, sizeof(unsigned int), fich->file);
    //lire la chaine "arbre serialisé"
    char * str = malloc(serieslen*sizeof(char)+1);
    
    fread(str, sizeof(char), serieslen, fich->file);
    str[serieslen] = '\0';
    //deserialiser l'arbre
    arbre a = deserialisation(&str);
    //decoder bit a bit et ecrire dans dest

    FILE * f = NULL;
    f = fopen(dest, "w");
    if(f == NULL){
        puts("Erreur de\'ecriture de fichier.");
        exit(EXIT_FAILURE);
    }


    decodage_fichier_aux(fich, a, a, f);



    //done
    fclose(f);
    closef(fich);
}

