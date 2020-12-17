
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char * argv[]) {

    if(argc == 2) {
        if(strcmp(argv[1], "help") == 0) {
            puts("Compression: ./huff encode fichiersource.txt [fichierdest.bin]");
            puts("Decompression: ./huff decode fichiersource.bin [fichierdest.text]");
            puts("[]: optionel");
        }else{
            printf("Erreur: option %s inexistante.", argv[1]);

        }
        exit(EXIT_FAILURE);

    }


    if(argc < 4){
        puts("Erreur: nombre d'arguments insuffisant. Veuillez reessayer.");
        exit(EXIT_FAILURE);
    }

    char * src = argv[2];
    char * dest;
    if(argc == 3) 
        dest = src;
    else 
        dest = argv[3];

    
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