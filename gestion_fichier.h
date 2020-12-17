#include <stdio.h>

#define BLOCK_SIZE 4096

typedef struct {
    FILE * file;
    char mode;
    unsigned char record[BLOCK_SIZE];
    int record_length ;
    int i_record;
    char octet[8];
    int i_octet;
    int nb_octets;

} Bin_file;

Bin_file *openf(char*, char);
void write_b(Bin_file*, char);
char read_b(Bin_file*);
int closef(Bin_file*);
char * fichier_to_str(char*);