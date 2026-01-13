#include "menu.h"

int menu_show() {           	
	printf("\n╔═══════════════════════╗\n║ 1. Test               ║\n║ 2. Test               ║\n║ 3. Test               ║\n║ 0. Wyjscie z programu ║\n╚═══════════════════════╝\n>> ");

	int choice;
	scanf("%d", &choice);
	switch (choice) {
		default:
			printf("[!] Wybrana opcja nie istnieje\n");
			return -1;
		case 0:
			return 0;
		case 1:
			printf("option 1\n");
			return 1;
		case 2:
			printf("option 2\n");
			return 2;
		case 3:
			printf("option 3\n");
			return 3;
	}
}
