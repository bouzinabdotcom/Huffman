#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion_fichier.h"


//convertit un entier en son equivalent en binaire ex: 2 => 00000010 (tableau de 8 char)
void expand_byte (unsigned char x, char * octet)
{
    int i ; //iterateur
    for (i=7 ; i>=0 ; i--) { // pour i de 7 a 0
        octet[i] = '0'+(x%2) ; //reste de div par 2 au bit de poid faible
        x = x>>1 ;//decalage logique a droite d'un seul bit
    }
} 

//Ouvre et initialise un fichier binaire
Bin_file *openf(char* filename, char mode) {
    Bin_file * f = NULL;
    f = (Bin_file *)malloc(sizeof(Bin_file));
    f->mode = mode;

    f->file = NULL;    
    //si mode == 'r' => on utilise "rb" dans la fonction fopen
    //sinon c'est "wb" qu'on utilise
    f->file = fopen(filename, f->mode=='r' ? "rb" : "wb"); 

    if(f->file == NULL) return NULL;

    //init
    f->record_length = 0;
    f->i_record = 0;
    f->i_octet = 0;
    f->nb_octets = 0;

    return f;    
    
}

//Ecrit bit par bit dans un fichier output
void write_b(Bin_file* output, char bit) {
    unsigned char octet, b; 
    //octet: sert a recoder l'octet a ecrire en binaire
    //b: prend un seul bit 1 a la fois du bit le poid fort a celui de poid faible

    output->octet[output->i_octet++] = bit; //ajout du bit a l'octet a ecrire 
                                            //incrementer le compteur de bits de l'octet

    if(output->i_octet == 8) { //si tampon octet contient 8 bits
        octet = 0;
        b = 0x80; //128 ~ 0b10000000

        //convertion de l'octet en binaire
        for(int i = 0; i<8; i++) {
            if(output->octet[i] == '1')
                octet = octet | b;
            b = b>>1;
        }

        output->i_octet = 0; 
        output->record[output->i_record] = octet; 
        output->i_record++;
        output->nb_octets++;

        //ecriture dans le fichier
        if(output->i_record == BLOCK_SIZE) {
            fwrite(output->record, 1, BLOCK_SIZE, output->file);
            output->i_record = 0;
        }

    }


}


//lit le prochain bit du fichier binaire
char read_b(Bin_file* input) {

    char bit;

    //lecture d'un BLOCK du fichier input si on a lu tous les bits du block precedant..
    if(input->record_length == 0) {
        input->record_length = fread(input->record, 1, BLOCK_SIZE, input->file);
        input->i_record = 0;
        expand_byte(input->record[input->i_record++], input->octet);
        input->i_octet = 0;
        input->nb_octets += input->record_length;

    }

    bit = input->octet[input->i_octet++];

    //lecture du prochain octet si on a lu tous les bit du precedant
    if(input->i_octet == 8) {
        expand_byte(input->record[input->i_record++], input->octet);
        input->i_octet = 0;
        if(input->i_record == BLOCK_SIZE) 
            input->record_length = 0;
    }


    return bit;
}


int closef(Bin_file* fichier) {
    int nb_octets = fichier->nb_octets;
    unsigned char octet, b;

    if(fichier->mode == 'w') {
        if(fichier->i_octet != 0) {
            octet = 0;
            b = 0x80;
            for(int i=0; i<fichier->i_octet; i++) {
                if(fichier->octet[i] == '1')
                    octet = octet | b;
                b=b>>1;
            }
            fichier->record[fichier->i_record++] = octet;

            
            nb_octets++;
        }
        if (fichier->i_record != 0) {
            fwrite(fichier->record, 1, BLOCK_SIZE, fichier->file);
        }
    }
    fclose(fichier->file);
    free(fichier);
    return nb_octets;
}

int fichier_len (char * filename) {
    int count = 0;
    FILE *f = NULL;
    f = fopen(filename, "r");

    if(f) {
        while(!feof(f)) {
            count++;
            fgetc(f);
        }
    }

    return count-1;
}

char * fichier_to_str(char * filename) {

    FILE* f = NULL;
    f = fopen(filename, "r");

    if(f == NULL) return NULL;
    char *str = malloc(fichier_len(filename)*sizeof(char));
    
    int cpt = 0;

    do {
        str[cpt++] = fgetc(f);
    } while(!feof(f));

    str[cpt-1] = '\0';
    
    return str;
}
