// uebung_c001
#include <stdio.h>

int stringlenght(char * buffer){
    int i = 0;
    while(*buffer!='\0'){
        ++i;
        ++buffer;
    }
    return i;
}

int main()
{
    char gruss[] = "Hallo";
    printf("Lenght of string %d \n", stringlenght(gruss));
    return 0;
}
