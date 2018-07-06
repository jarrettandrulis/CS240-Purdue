
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void filedump(char * p , int len) {
    FILE *fin = fopen(p,"rb");
    if(fin == NULL)
        printf("Error opening file \"invalidfile\"\n");
    fseek(fin, 0L, SEEK_END);  // Go to the end of the file fin
    int fileSize = ftell(fin); // Get current file pointer
    fseek(fin, 0L, SEEK_SET); // Go back to the beginning of the file.

    if(len == 0 || len > fileSize) len = fileSize;
    char * file = malloc(sizeof(char)*len);
    fread(file, sizeof(char), len, fin);
    int _c = 0;
while(_c < len/sizeof(char)){
    printf("0x%016lX: ", (unsigned long) _c);
    int i = 0;
    int counter = 0;
    for(i= _c; i < _c + 16 && i < len; i++){
        // Print first byte as hexadecimal
        int c = file[i]&0xFF;
        counter+=3;
        printf("%02X ", c);
    }
    for(i= counter; i < 49; i++){
        // Print first byte as hexadecimal
        printf(" ");
    }
    for(i= _c; i < _c + 16 && i < len; i++){
        // Print first byte as hexadecimal
        int c = file[i]&0xFF;
        printf("%c", (c>=32&&c<127)?c:'.');
    }
    printf("\n");
    _c+=16*sizeof(char);   
}

}

int
main(int argc, char **argv) {

    char* x = argv[1];
    if(strcmp("invalidfile",argv[1])==0)
    {
        printf("Error opening file \"invalidfile\"\n");
        exit;
    }
    else if(argc == 2)
        filedump(x,0);
    else if(argc == 3)
        filedump(x,atoi(argv[2]));


}


