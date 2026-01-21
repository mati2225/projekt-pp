#include <stdio.h>
#include <string.h>
#include "file.h"
#include "data.h"

FILE* fptr = NULL;

int file_init(const char* path) {
    fptr = fopen(path, "rb");
    if (fptr == NULL) {
        perror("[!] Wystapil blad podczas otwierania pliku");
        return 0;
    }

    init_list(global_list);
    mech_object temp;

    while (fread(&temp, sizeof(mech_object), 1, fptr) == 1) {
        push_back(global_list, temp);
        //printf("%s %d %d %d %d %s %d\n", rr.model, rr.type, rr.reactor_power, rr.armor_health, rr.ammo, rr.assigned_pilot, rr.condition);
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

    /*size_t num_written = fwrite(&test1, sizeof(Mech), 1, fptr);
    if (num_written != 1) {
        perror("[!] blad");
        fclose(fptr);
        return 0;
    }*/
    
    fclose(fptr);
    return 1;
}