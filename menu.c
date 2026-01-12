#include "menu.h"

int menu_show() {
	printf("menu placeholder\n1.\n2.\n3.\n0.\n>> ");

	int choice;
	scanf("%d", &choice);
	switch (choice) {
		default:
			printf("[!] Wybrana opcja nie istnieje\n");
			return -1;
		case 0:
			printf("exit\n");
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
