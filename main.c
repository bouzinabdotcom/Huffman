
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char * argv[]) {

    if(argc < 4){
        puts("Erreur: nombre d'arguments insuffisant. Veuillez reessayer.");
        exit(EXIT_FAILURE);
    }
    
    if(strcmp(argv[1], "encode")==0) {
        puts("Compression en cours...");
        codage_fichier(argv[2], argv[3]);
        puts("Compression terminée!");
    }
    else if(strcmp(argv[1], "decode")==0) {
        puts("Decompression en cours...");
        decodage_fichier(argv[2], argv[3]);
        puts("Decompression terminée!");
    } else {
        printf("Erreur: option %s inexistante.", argv[1]);
        exit(EXIT_FAILURE);
    }

    return 0;
}