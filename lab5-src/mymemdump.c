#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void mymemdump(FILE * fd, char * p , int len) {
 // Add your code here.
 // You may see p as an array.
 // p[0] will return the element 0
 // p[1] will return the element 1 and so on
int _c = 0;
while(_c < len){
    fprintf(fd, "0x%016lX: ", (unsigned long) p+_c);
    int i = 0;
    int counter = 0;
    for(i= _c; i < _c + 16 && i < len; i++){
        // Print first byte as hexadecimal
        int c = p[i]&0xFF;
        counter+=3;
        fprintf(fd, "%02X ", c);
    }
    for(i= counter; i < 49; i++){
        // Print first byte as hexadecimal
        fprintf(fd, "%s", " ");
    }
    for(i= _c; i < _c + 16 && i < len; i++){
        // Print first byte as hexadecimal
        int c = p[i]&0xFF;
        fprintf(fd, "%c", (c>=32&&c<127)?c:'.');
    }
    fprintf(fd, "\n");
    _c+=16;
}

}
