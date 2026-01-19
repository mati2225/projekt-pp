#include "menu.h"
#include "data.h"

//te funkcje sa prywatne i sa dostepne tylko w obrebie menu.c
void menu_add_new_mech();
int menu_edit_mech_data();
void menu_print_mech_data();
void menu_display_mech_list();

int menu_show() {
	printf("\n╔═[GLOWNE MENU]═══════════════════════════════╗\n║ 1. Dodaj nowego mecha                       ║\n║ 2. Edytuj wybrana jednostke                 ║\n║ 3. Wyswietl informacje o wybranej jednostce ║\n║ 4. Wyswietl wszystkie jednostki             ║\n║ 0. Wyjscie z programu                       ║\n╚═════════════════════════════════════════════╝\n>> ");
	char choice;
	scanf("%c", &choice);
	switch (choice) {
		default:
			printf("[!] Wybrana opcja nie istnieje\n");
			return -1;
		case '0':
			return 0;
		case '1':
			menu_add_new_mech();
			return 1;
		case '2':
			while (menu_edit_mech_data() != 0) {}
			return 2;
		case '3':
			menu_print_mech_data();
			return 3;
		case '4':
			menu_display_mech_list();
			return 4;
	}
}

void menu_add_new_mech() {
	char model[101], pilot[51];
	char* class_converted = NULL;
	int class;
	while (true) {
		printf("\n╔═[DODAWANIE MECHA]══════════════════╗\n║ WPROWADZ WYMAGANE DANE             ║\n╚════════════════════════════════════╝\n-= Model (unikalna nazwa mecha, identyfikator jednostki)  \n>> ");
		while (scanf(" %100[^\n]s", model) != 1) {
			printf("[!] Wprowadzono bledne dane\n-= Model (unikalna nazwa mecha, identyfikator jednostki)  \n>> ");
		}

		printf("-= Klasa (0 - Szturmowy; 1 - Wsparcia ogniowego; 2 - Rekonesansowy; 3 - obronny; )\nWprowadzenie wartosci z przedzialu innego niz <0; 3> oznacza brak klasy\n>> ");
		while (scanf(" %d", &class) != 1) {
			printf("[!] Wprowadzono bledne dane\n-= Klasa (0 - Szturmowy; 1 - Wsparcia ogniowego; 2 - Rekonesansowy; 3 - obronny; )\nWybranie wartosci z przedzialu innego niz <0; 3> oznacza brak klasy\n>> ");
		}
		class_converted = mech_class_to_str((enum MechClass)class);

		printf("-= Przydzielony pilot (Imie i nazwisko)\n>> ");
		while (scanf(" %50[^\n]s", pilot) != 1) {
			printf("[!] Wprowadzono bledne dane\n-= Przydzielony pilot (Imie i nazwisko)\n>> ");
		}

		printf("\n╔═[DODAWANIE MECHA]══════════════════╗\n║ WERYFIKACJA WPROWADZONYCH DANYCH   ║\n╚════════════════════════════════════╝\n- MODEL: %s \n- KLASA: %s\n- PRZYDZIELONY PILOT: %s\nCzy wprowadzone dane sa poprawne? (1 - TAK; 0 - NIE): ", model, class_converted, pilot);
		char option;
		scanf(" %c", &option);
		if (option != '0') {
			break;
		}
		else {
			continue;
		}
	}
}

int menu_edit_mech_data() {
	printf("╔═[EDYTOWANIE JEDNOSTKI]═════════╗\n║ 1. Zmien klase mecha           ║\n║ 2. Zwieksz moc reaktora        ║\n║ 3. Zmniejsz moc reaktora       ║\n║ 4. Napraw pancerz              ║\n║ 5. Uzupelnij amunicje          ║\n║ 6. Przydziel pilota            ║\n║ 7. Zmien stan techniczny       ║\n║ 8. Usun jednostke z ewidencji  ║\n║ 0. Powrot do poprzedniego menu ║\n╚════════════════════════════════╝\n>> ");
	char choice;
	scanf("%c", &choice);
	switch (choice) {
		default:
			printf("[!] Wybrana opcja nie istnieje\n");
			return -1;
		case '0':
			return 0;
		case '1': // Zmien klase mecha
			printf("- 1\n");
			return 1;
		case '2': // Zwieksz moc reaktora
			printf("- 2\n");
			return 2;
		case '3': // Zmniejsz moc reaktora
			printf("- 3\n");
			return 3;
		case '4': // Napraw pancerz
			printf("- 4\n");
			return 4;
		case '5': // Uzupelnij amunicje
			printf("- 5\n");
			return 5;
		case '6': // Przydziel pilota
			printf("- 6\n");
			return 5;
		case '7': // Zmien stan techniczny
			printf("- 7\n");
			return 5;
		case '8': // Usun jednostke z ewidencji
			printf("- 8\n");
			return 5;
	}
}

void menu_print_mech_data() {
	printf("option 3\n");
}

void menu_display_mech_list() {
	printf("option 4\n");
}
