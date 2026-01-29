#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"

#define ENTRIES 100

void generate_mechs(mech_object* mechs, size_t count);

void generate_mechs(mech_object* mechs, size_t count) {
    const char* prefixes[] = {
        "ATLAS", "TITAN", "RAVEN", "PHOENIX", "ODIN",
        "ARES", "NEMESIS", "HADES", "ZEUS", "ORION"
    };

    const char* cores[] = {
        "NOVA", "IRON", "VOID", "STEEL", "STORM",
        "FURY", "ECHO", "EMBER", "SHADOW", "VORTEX"
    };

    const char* suffixes[] = {
        "MK", "X", "PRIME", "CORE", "UNIT",
        "FRAME", "GEAR", "DRIVE", "PROTO", "ALPHA"
    };

    const char* pilots[] = {
        "Kowalski", "Nowak", "Raven", "Wolf", "Shadow",
        "Orion", "Vega", "Hunter", "Blaze", "Steel"
    };

    size_t p_count = sizeof(prefixes) / sizeof(prefixes[0]);
    size_t c_count = sizeof(cores) / sizeof(cores[0]);
    size_t s_count = sizeof(suffixes) / sizeof(suffixes[0]);
    size_t pilot_count = sizeof(pilots) / sizeof(pilots[0]);

    srand((unsigned)time(NULL));

    for (size_t i = 0; i < count; i++) {
        snprintf(mechs[i].model, sizeof(mechs[i].model),
                 "%s-%s-%s-%03zu",
                 prefixes[rand() % p_count],
                 cores[rand() % c_count],
                 suffixes[rand() % s_count],
                 i + 1);

        mechs[i].type = rand() % 4;
        mechs[i].reactor_power = rand() % 101;
        mechs[i].armor_health = rand() % 1001;
        mechs[i].ammo = rand() % 1001;

        strncpy(mechs[i].assigned_pilot,
                pilots[rand() % pilot_count],
                sizeof(mechs[i].assigned_pilot) - 1);
        mechs[i].assigned_pilot[sizeof(mechs[i].assigned_pilot) - 1] = '\0';

        mechs[i].condition = rand() % 5;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
		fprintf(stderr, "Blad: Nie podano pliku z danymi! Poprawne uzycie: %s <sciezka do pliku>\n", argv[0]);
		return 1;
	}

    const char* path = argv[1];
    FILE* fptr = fopen(path, "wb");
    mech_object objects[ENTRIES];
    generate_mechs(objects, ENTRIES);

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
        fprintf(stderr, "Blad: Odczytano tylko %zu elementow\n", read);
    }
    fclose(fptr);

    printf("[datagen]:\n");
    for (int i = 0; i < ENTRIES; i++) {
        printf("%s, %d, %d, %d, %d, %s, %d\n", backup[i].model, backup[i].type, backup[i].reactor_power, backup[i].armor_health, backup[i].ammo, backup[i].assigned_pilot, backup[i].condition);
    }

    return 0;
}