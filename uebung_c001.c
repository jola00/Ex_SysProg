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

char* strcopy(const char* source, char* dest) {
    if (source == NULL)
        return NULL;
    
    while(*source)   {
        *dest++ = *source++;
    }
}

int main()
{
    // initial string
    char gruss[] = "Hallo";

    // test of stringlenght
    printf("Lenght of string %d \n", stringlenght(gruss));

    // test of strcopy
    char gruss_copy[10];
    strcopy(gruss, gruss_copy);
    printf(gruss_copy);
    return 0;
}
