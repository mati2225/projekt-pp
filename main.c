#include <stdio.h>
#include "menu.h"

void show_intro();

int main() {
	show_intro();

	while (menu_show() != 0) {}

	printf("[*] Wylaczanie programu...\n");
	return 0;
}

void show_intro() {
	printf("╔═[CENTRALNY SYSTEM EWIDENCJI MECHOW]═╗\n║ Autorzy:                            ║\n║ - Mateusz Tomczuk                   ║\n║ - Michal Zwierzynski                ║\n║ - Kuba Kirej                        ║\n╚═════════════════════════════════════╝");
}
