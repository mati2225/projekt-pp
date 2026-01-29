#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "data.h"

FILE* fptr = NULL;

int file_init(const char* path) {
    fptr = fopen(path, "rb");
    if (fptr == NULL) {
        perror("[!] Wystapil blad podczas otwierania pliku");
        return 0;
    }

    init_list(&global_list);
    mech_object temp;

    while (fread(&temp, sizeof(mech_object), 1, fptr) == 1) {
        push_back(&global_list, temp);
    }

    fclose(fptr);
    return 1;
}

int file_save(const char* path) {
    fptr = fopen(path, "wb");
    if (fptr == NULL) {
        perror("[!] Wystapil blad podczas otwierania pliku");
        return 0;
    }

    int elements = count_elements(&global_list);
    size_t out_size;
    mech_object* allObjects = list_to_array(&global_list, &out_size);
    size_t num_written = fwrite(allObjects, sizeof(mech_object), elements, fptr);

    if (num_written != (size_t) elements) {
        fprintf(stderr, "[!] Zapisano tylko %zu z %d elementow", num_written, elements);
        fclose(fptr);
        return 0;
    }

    free(allObjects);
    allObjects = NULL;
    
    fclose(fptr);
    return 1;
}