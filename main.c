#include <stdio.h>
#include "menu.h"

void showIntro();

int main() {
	showIntro();

	while (menu_show() != 0) {

	}

	printf("Wylaczanie programu...\n");
	return 0;
}

void showIntro() {
	printf("=== intro ===\n");
}
