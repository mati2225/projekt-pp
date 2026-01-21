#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "file.h"

void show_intro();

int main(int argc, char** argv) {
	if (argc < 2) {
		fprintf(stderr, "Blad: Nie podano pliku z danymi! Poprawne uzycie: %s <sciezka do pliku>\n", argv[0]);
		return 1;
	}

	const char* path = argv[1];
	
	if (!file_init(path))
		return 1;

	show_intro();

	while (menu_show() != 0);

	printf("[*] Wylaczanie programu...\n");
	return 0;
}

void show_intro() {
	printf("╔═[CENTRALNY SYSTEM EWIDENCJI MECHOW]═╗\n║ Autorzy:                            ║\n║ - Mateusz Tomczuk                   ║\n║ - Michal Zwierzynski                ║\n║ - Kuba Kirej                        ║\n╚═════════════════════════════════════╝");
}
