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
    char gruss[] = "Hallo";
    printf("Lenght of string %d \n", stringlenght(gruss));
    char gruss1[10];
    strcopy(gruss, gruss1);
    printf(gruss1);
    return 0;
}
