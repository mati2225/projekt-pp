#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "file.h"

//#define DEBUG

int main(int argc, char** argv) {
#ifndef DEBUG
	if (argc < 2) {
		fprintf(stderr, "Błąd: Nie podano pliku z danymi! Poprawne użycie: %s <ścieżka do pliku>\n", argv[0]);
		return 1;
	}

	const char* path = argv[1];
#else
	const char* path = "test2.bin";
#endif

	if (!file_init(path)) return 1;

	menu_show_intro();

	while (menu_show() != 0);

	if (!file_save(path)) return 1;

	printf("[*] Zapisywanie danych i wyłączanie programu...\n");
	return 0;
}
