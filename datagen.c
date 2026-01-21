#include <stdio.h>
#include "data.h"

#define ENTRIES 4

int main(int argc, char** argv) {
    if (argc < 2) {
		fprintf(stderr, "Blad: Nie podano pliku z danymi! Poprawne uzycie: %s <sciezka do pliku>\n", argv[0]);
		return 1;
	}

	const char* path = argv[1];
    mech_object objects[ENTRIES] = {
        {"test1", 1, 100, 100, 100, "imie nazwisko", 0},
        {"test2", 0, 0, 26, 10, "", 3},
        {"abcdefghijklmnopqrstuvwxyz", 2, 50, 33, 45, "imie nazwisko", 1},
        {"test3", 0, 100, 1, 90, "pilot", 3}
    };

    FILE* fptr = fopen(path, "wb");
    if (fptr == NULL) {
        perror("[!] Wystapil blad podczas otwierania pliku");
        return 1;
    }

    size_t written = fwrite(objects, sizeof(mech_object), ENTRIES, fptr);
    if (written != ENTRIES) {
        fprintf(stderr, "Blad: Zapisano tylko %zu elementow\n", written);
    }
    fclose(fptr);

    mech_object backup[ENTRIES];
    fptr = fopen(path, "rb");
    if (fptr == NULL) {
        perror("[!] Wystapil blad podczas otwierania pliku");
        return 1;
    }

    size_t read = fread(backup, sizeof(mech_object), ENTRIES, fptr);
    if (read != ENTRIES) {
        fprintf(stderr, "Blad: Odczytano tylko %zu elementow\n", written);
    }
    fclose(fptr);

    printf("[datagen]:\n");
    for (int i = 0; i < ENTRIES; i++) {
        printf("%s, %d, %d, %d, %d, %s, %d\n", backup[i].model, backup[i].type, backup[i].reactor_power, backup[i].armor_health, backup[i].ammo, backup[i].assigned_pilot, backup[i].condition);
    }

    return 0;
}