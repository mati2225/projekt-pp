#include <stdio.h>
#include <string.h>
#include "file.h"

FILE* fptr = NULL;

int file_init(const char* path) {
    fptr = fopen(path, "r");
    if (fptr == NULL) {
        perror("[!] Wystapil blad podczas otwierania pliku");
        return 0;
    }

    char buf[50];
    while (fgets(buf, 50, fptr)) {
        printf("%s", buf);
    }

    /*while (fscanf(fptr, "", ) == 1) {

    }*/


    fclose(fptr);
    return 1;
}
