#include <string.h>
#include <stdlib.h>
#include "menu.h"
#include "data.h"

void menu_add_new_mech();
int menu_edit_mech_data(mech_object* mechObj);
int menu_display_mech_list();
void menu_fancy_table_print(const mech_object* mechs, size_t count);
void menu_list_print(List* list);
int digits(int value);

int menu_show() {
	printf("\n╔═[GŁÓWNE MENU]═══════════════════════════════╗\n║ 1. Dodaj nowego mecha                       ║\n║ 2. Edytuj wybraną jednostkę                 ║\n║ 3. Wszystkie jednostki                      ║\n║ 0. Wyjście z programu                       ║\n╚═════════════════════════════════════════════╝\n>> ");
	char choice;
	scanf(" %c", &choice);
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
			printf("Wpisz model (unikalny identyfikator) jednostki: ");
			char model[101];
			getchar();
			while (scanf("%100[^\n]s", model) != 1) {
				printf("[!] Wprowadzono błędne dane\nWpisz model (unikalny identyfikator) jednostki: ");
				while(getchar() != '\n');
			}

			mech_object* mechObj = find_by_exact_model(&global_list, model);
			if (mechObj == NULL) {
				printf("[!] Jednostka o podanym modelu nie istnieje");
				return 2;
			}

			while (menu_edit_mech_data(mechObj) != 0);
			return 2;
		case '3':
			while(menu_display_mech_list() != 0);
			return 3;
	}
}

void menu_add_new_mech() {
	char model[101], pilot[51];
	char* type_converted = NULL;
	int type;
	while (true) {
		printf("\n╔═[DODAWANIE MECHA]══════════════════╗\n║ WPROWADŹ WYMAGANE DANE             ║\n╚════════════════════════════════════╝\nModel (unikalna nazwa mecha, identyfikator jednostki)  \n>> ");
		
		getchar();
		while (scanf("%100[^\n]s", model) != 1) {
			printf("[!] Wprowadzono błędne dane\nModel (unikalna nazwa mecha, identyfikator jednostki)  \n>> ");
			while(getchar() != '\n');
		}

		mech_object* mechObj = find_by_exact_model(&global_list, model);
		if (mechObj != NULL) {
			printf("[!] Jednostka o podanym modelu już istnieje. Nazwa nowej jednostki musi być unikalna");
			break;
		}

		printf("Klasa (0 - Szturmowy; 1 - Wsparcia ogniowego; 2 - Rekonesansowy; 3 - Obronny; )\nWprowadzenie wartości z przedziału innego niż <0; 3> oznacza brak klasy\n>> ");
		
		getchar();
		while (scanf("%d", &type) != 1) {
			printf("[!] Wprowadzono błędne dane\nKlasa (0 - Szturmowy; 1 - Wsparcia ogniowego; 2 - Rekonesansowy; 3 - Obronny; )\nWybranie wartości z przedziału innego niż <0; 3> oznacza brak klasy\n>> ");
			while(getchar() != '\n');
		}
		
		type_converted = mech_type_to_str((enum mech_type) type);

		printf("Przydzielony pilot (Imię i nazwisko)\nPodaj spację aby pozostawić jednostkę bez pilota\n>> ");
		
		getchar();
		while (scanf("%50[^\n]s", pilot) != 1) {
			printf("[!] Wprowadzono błędne dane\nPrzydzielony pilot (Imię i nazwisko)\nPodaj spację aby pozostawić jednostkę bez pilota\n>> ");
			while(getchar() != '\n');
		}

		printf("\n╔═[DODAWANIE MECHA]══════════════════╗\n║ WERYFIKACJA WPROWADZONYCH DANYCH   ║\n╚════════════════════════════════════╝\nMODEL: %s \nKLASA: %s\nPRZYDZIELONY PILOT: %s\nCzy wprowadzone dane są poprawne?\nWpisz literę 'T' lub 't' aby dodać jednostkę\nWpisz literę 'N' lub 'n' aby wprowadzić dane ponownie\n>>", model, type_converted, pilot);
		
		char option;
		getchar();
		scanf("%c", &option);
		if (option == 'T' || option == 't') {
			mech_object* newObject = malloc(sizeof(mech_object));
			strcpy(newObject->model, model);
			if (pilot[0] == ' ') {
				strcpy(newObject->assigned_pilot, "-");
			} else {
				strcpy(newObject->assigned_pilot, pilot);
			}
			newObject->type = (enum mech_type)type;
			newObject->reactor_power = 0;
			newObject->armor_health = 1000;
			newObject->ammo = 1000;
			newObject->condition = (enum mech_condition)0;
			push_back(&global_list, *newObject);
			break;
		}
		else {
			continue;
		}
	}
}

int menu_edit_mech_data(mech_object* mechObj) {
	printf("\n╔═[EDYTOWANIE JEDNOSTKI]═════════╗\n║ 1. Zmień nazwę mecha           ║\n║ 2. Zmień klasę mecha           ║\n║ 3. Zwiększ moc reaktora        ║\n║ 4. Zmniejsz moc reaktora       ║\n║ 5. Napraw pancerz              ║\n║ 6. Uzupełnij amunicję          ║\n║ 7. Przydziel pilota            ║\n║ 8. Zmień stan techniczny       ║\n║ 9. Usuń jednostkę z ewidencji  ║\n║ 0. Powrót do poprzedniego menu ║\n╚════════════════════════════════╝\n>> ");
	
	int power = 0, power_new = 0;
	
	char choice;
	getchar();
	scanf("%c", &choice);
	switch (choice) {
		default:
			printf("[!] Wybrana opcja nie istnieje\n");
			return -1;
		case '0':
			return 0;
		case '1': //zmien nazwe mecha
			printf("Obecna nazwa jednostki: \"%s\"\nPodaj nową nazwę\n>> ", mechObj->model);
			char new_name[101];
			getchar();

			while (scanf("%100[^\n]s", new_name) != 1) {
				printf("[!] Wprowadzono błędne dane\nPodaj nową nazwę\n>> ");
				while(getchar() != '\n');
			}

			printf("[!] Błąd: Nazwa (model) mecha jest jego identyfikatorem i nie można jej zmieniać");

			return 1;
		case '2': // Zmien klase mecha
			printf("Obecna klasa jednostki \"%s\": %s\n", mechObj->model, mech_type_to_str(mechObj->type));
			printf("Podaj nową klasę (0 - Szturmowy; 1 - Wsparcia ogniowego; 2 - Rekonesansowy; 3 - Obronny; )\nWprowadzenie wartości z przedziału innego niż <0; 3> oznacza brak klasy\n>> ");
			
			int type;
			while (scanf("%d", &type) != 1) {
				printf("[!] Wprowadzono błędne dane\nPodaj nową klasę (0 - Szturmowy; 1 - Wsparcia ogniowego; 2 - Rekonesansowy; 3 - Obronny; )\nWybranie wartości z przedziału innego niż <0; 3> oznacza brak klasy\n>> ");
				while(getchar() != '\n');
			}

			mechObj->type = (enum mech_type)type;

			printf("[i] Klasa mecha zostala zmieniona\n");
			return 2;
		case '3': // Zwieksz moc reaktora
			printf("Obecna moc reaktora jednostki \"%s\": %d\n", mechObj->model, mechObj->reactor_power);
			printf("Podaj o jaką wartość chcesz zwiększyć moc: ");
			
			while (scanf("%d", &power) != 1) {
				printf("[!] Wprowadzono błędne dane\n-= Podaj o jaką wartość chcesz zwiększyć moc: ");
				while(getchar() != '\n');
			}

			power_new = mechObj->reactor_power + power;

			if (power_new > 100) {
				printf("[!] Nie udało się zwiększyć mocy reaktora: moc docelowa wykracza poza maksymalną dozwoloną wartość (100 MW)\n");
			} else {
				mechObj->reactor_power = power_new;
				printf("[i] Zwiększono moc reaktora\n");
			}

			return 3;
		case '4': // Zmniejsz moc reaktora
			printf("Obecna moc reaktora jednostki \"%s\": %d\n", mechObj->model, mechObj->reactor_power);
			printf("Podaj o jaką wartość chcesz zmniejszyć moc: ");
			
			while (scanf("%d", &power) != 1) {
				printf("[!] Wprowadzono błędne dane\nPodaj o jaką wartość chcesz zmniejszyć moc: ");
				while(getchar() != '\n');
			}
			
			power_new = mechObj->reactor_power - power;
			
			if (power_new < 0) {
				printf("[!] Nie udało się zmniejszyć mocy reaktora: moc docelowa wykracza poza minimalną dozwoloną wartość (0 MW)\n");
			} else {
				mechObj->reactor_power = power_new;
				printf("[i] Zmniejszono moc reaktora\n");
			}
			
			return 4;
		case '5': // Napraw pancerz
			printf("Obecny stan pancerza jednostki \"%s\": %d\n", mechObj->model, mechObj->armor_health);
			
			if (mechObj->armor_health < 2000) {
				mechObj->armor_health = 2000;
			}

			printf("[i] Naprawiono pancerz\n");
			return 5;
		case '6': // Uzupelnij amunicje
			printf("Obecna ilość amunicji jednostki \"%s\": %d\n", mechObj->model, mechObj->ammo);
			
			if (mechObj->armor_health < 1000) {
				mechObj->armor_health = 1000;
			}

			printf("[i] Uzupełniono amunicję\n");
			return 6;
		case '7': // Przydziel pilota
			printf("Obecnie przydzielony pilot jednostki \"%s\": %s\n", mechObj->model, mechObj->assigned_pilot);
			printf("Podaj imię i nazwisko pilota (max. 50 znaków)\nW przypadku podania spacji nie zostanie przydzielony żaden pilot\n>> ");
			
			getchar();
			char new_pilot[51];
			while (scanf("%50[^\n]s", new_pilot) != 1) {
				printf("[!] Wprowadzono błędne dane\nPodaj imię i nazwisko pilota (max. 50 znaków)\nW przypadku podania spacji nie zostanie przydzielony żaden pilot\n>> ");
				while(getchar() != '\n');
			}

			if (new_pilot[0] == ' ') {
				strcpy(mechObj->assigned_pilot, "-");
				printf("[i] Nie przydzielono żadnego pilota\n");
			} else {
				strcpy(mechObj->assigned_pilot, new_pilot);
				printf("[i] Przydzielono nowego pilota\n");
			}

			return 7;
		case '8': // Zmien stan techniczny
			printf("Obecny stan techniczny jednostki \"%s\": %s\n", mechObj->model, mech_condition_to_str(mechObj->condition));
			printf("Podaj nowy stan techniczny (0 - Sprawny; 1 - Wymaga przegledu; 2 - Uszkodzony; 3 - W naprawie; 4 - W demontażu; )\n>> ");
			
			int condition;
			while (scanf("%d", &condition) != 1) {
				printf("[!] Wprowadzono błędne dane\nPodaj nowy stan techniczny (0 - Sprawny; 1 - Wymaga przeglądu; 2 - Uszkodzony; 3 - W naprawie; 4 - W demontażu; )\n>> ");
				while(getchar() != '\n');
			}

			if (condition < 0 || condition > 4) {
				printf("[!] Wprowadzono wartość z przedzialu innego niż <0; 4>");
				return 7;
			}

            mechObj->condition = (enum mech_condition)condition;
			
			printf("[i] Stan techniczny mecha został zmieniony\n");
			return 8;
		case '9': // Usun jednostke z ewidencji	
			printf("!!!!!! OSTRZEŻENIE !!!!!!\nCzy napewno chcesz usunąć jednostkę \"%s\"? (operacji nie można cofnąć)\nWpisz literę 'T' lub 't' aby usunąć jednostkę\nWpisz literę 'N' lub 'n' aby anulować\n>> ", mechObj->model);
			
			char choicee;
			getchar();
			scanf("%c", &choicee);
			
			if (choicee == 'T' || choicee == 't') {
				if (mechObj->condition == W_NAPRAWIE || mechObj->condition == W_DEMONTAZU) {
					remove_first(&global_list, *mechObj);
					printf("[i] Jednostka została usunięta");
				} else {
					printf("[!] Błąd: Nie można usunąć jednostki \"%s\" gdyż nie jest w stanie naprawy lub demontażu", mechObj->model);
				}
			} else {
				printf("[i] Operacja została anulowana");
			}
			
			return 0;
	}
}

int menu_display_mech_list() {
    printf("\n╔═[LISTA WSZYSTKICH OBIEKTÓW]══════════════════════╗\n║ 1 - Pokaż wszystkie obiekty                      ║\n║ 2 - Wyszukaj po nazwie                           ║\n║ 3 - Sortuj alfabetycznie wg nazwy                ║\n║ 4 - Sortuj malejąco wg wybranego pola liczbowego ║\n║ 5 - Sortuj rosnąco wg wybranego pola liczbowego  ║\n║ 6 - Filtruj wg wybranego pola liczbowego         ║\n║ 0 - Powrót do poprzedniego menu                  ║\n╚══════════════════════════════════════════════════╝\n>> ");

    char choice;
	int filter;
	getchar();
    scanf("%c", &choice);
    switch (choice) {
        default:
            printf("[!] Wybrana opcja nie istnieje\n");
            return -1;
        case '0':
            return 0;
        case '1':
			//print_forward(&global_list);
			menu_list_print(&global_list);
			printf("\nLICZBA WSZYSTKICH JEDNOSTEK: %d\n", count_elements(&global_list));
            return 1;
        case '2':
			printf("Wpisz model (nazwę/unikalny identyfikator) jednostki: ");
			
			char model[101];
			getchar();
			while (scanf("%100[^\n]s", model) != 1) {
				printf("[!] Wprowadzono błędne dane\nWpisz model (nazwę/unikalny identyfikator) jednostki: ");
				while(getchar() != '\n');
			}

			printf("=== WYNIKI WYSZUKIWANIA DLA \"%s\":\n", model);
			
			int results = list_by_model(&global_list, model);
			
			if (results < 1) {
				printf("-\n=== NIE ZNALEZIONO ŻADNEJ JEDNOSTKI O PODANEJ NAZWIE\n");
			} else {
				printf("=== ZNALEZIONO %d WYNIKÓW\n", results);
			}
			
            return 2;
        case '3': //sortowanie alfabetyczne wg nazwy
			List sorted = merge_sort_list(&global_list);
			printf("Sortowanie alfabetyczne według nazwy modelu\n");
			menu_list_print(&sorted);
			free_list(&sorted);
            return 3;
        case '4': //malejaco pole liczbowe
			printf("Wybierz pole\n1 - Moc reaktora\n2 - Stan pancerza\n3 - Amunicja\n>> ");
			getchar();
			scanf("%d", &filter);

			List* num_sort1 = NULL;
			switch (filter) {
				case 1:
					num_sort1 = sort_by_reactor_power(&global_list, SORT_DESC);
					printf("Sortowanie malejąco po mocy reaktora\n");
					break;
				case 2:
					num_sort1 = sort_by_armor(&global_list, SORT_DESC);
					printf("Sortowanie malejąco po stanie pancerza\n");
					break;
				case 3:
					num_sort1 = sort_by_ammo(&global_list, SORT_DESC);
					printf("Sortowanie malejąco po amunicji\n");
					break;
				default:
					printf("[!] Wybrane pole liczbowe nie istnieje\n");
					return 6;
			}
			menu_list_print(num_sort1);
			free_list(num_sort1);
            return 4;
        case '5': //rosnaco pole liczbowe
			printf("Wybierz pole\n1 - Moc reaktora\n2 - Stan pancerza\n3 - Amunicja\n>> ");
			getchar();
			scanf("%d", &filter);

			List* num_sort2 = NULL;
			switch (filter) {
				case 1:
					num_sort2 = sort_by_reactor_power(&global_list, SORT_ASC);
					printf("Sortowanie rosnąco po mocy reaktora\n");
					break;
				case 2:
					num_sort2 = sort_by_armor(&global_list, SORT_ASC);
					printf("Sortowanie rosnąco po stanie pancerza\n");
					break;
				case 3:
					num_sort2 = sort_by_ammo(&global_list, SORT_ASC);
					printf("Sortowanie rosnąco po amunicji\n");
					break;
				default:
					printf("[!] Wybrane pole liczbowe nie istnieje\n");
					return 6;
			}
			menu_list_print(num_sort2);
			free_list(num_sort2);
            return 5;
        case '6': //filtruj wg pola liczbowego
			printf("Wybierz pole\n1 - Moc reaktora\n2 - Stan pancerza\n3 - Amunicja\n>> ");
			getchar();
			scanf("%d", &filter);
			
			printf("Wpisz wartość minimalną\n>> ");
			int threshold;
			getchar();
			scanf("%d", &threshold);
			
			List* filtered = NULL;
			switch (filter) {
				case 1:
					filtered = filter_by_reactor_power(&global_list, threshold);
					printf("Filtrowanie po mocy reaktora, min. %d MW\n", threshold);
					break;
				case 2:
					filtered = filter_by_armor(&global_list, threshold);
					printf("Filtrowanie po stanie pancerza, min. %d\n", threshold);
					break;
				case 3:
					filtered = filter_by_ammo(&global_list, threshold);
					printf("Filtrowanie po amunicji, min. %d\n", threshold);
					break;
				default:
					printf("[!] Wybrane pole liczbowe nie istnieje\n");
					return 6;
			}
			menu_list_print(filtered);
			free_list(filtered);
            return 6;
    }
}

void menu_show_intro() {
	printf("╔═[CENTRALNY SYSTEM EWIDENCJI MECHÓW]═╗\n║ Autorzy:                            ║\n║ - Mateusz Tomczuk                   ║\n║ - Michal Zwierzyński                ║\n║ - Kuba Kirej                        ║\n╚═════════════════════════════════════╝");
}

int digits(int value) {
    int d = (value <= 0) ? 1 : 0;
    while (value) {
        value /= 10;
        d++;
    }
    return d;
}

void menu_list_print(List* list) {
	size_t out_size;
    mech_object* mechs = list_to_array(list, &out_size);
	int list_len = count_elements(list);
	if (mechs == NULL || list_len != (int)out_size) {
		printf("[!] Błąd w drukowaniu listy\n");
	} else {
		menu_fancy_table_print(mechs, list_len);
	}
	free(mechs);
	mechs = NULL;
}

void menu_fancy_table_print(const mech_object* mechs, size_t count) {
    size_t w_model = strlen("Model");
	size_t w_type = strlen("Klasa");
    size_t w_pilot = strlen("Pilot");
    size_t w_reactor = strlen("Moc Reaktora");
    size_t w_armor = strlen("Pancerz");
    size_t w_ammo = strlen("Amunicja");
	size_t w_condition = strlen("Stan Techniczny");

	char* type_str = NULL;
	char* condition_str = NULL;
    for (size_t i = 0; i < count; i++) {
		type_str = mech_type_to_str(mechs[i].type);
		condition_str = mech_condition_to_str(mechs[i].condition);

        if (strlen(mechs[i].model) > w_model)
            w_model = strlen(mechs[i].model);

		if (strlen(type_str) > w_type)
            w_type = strlen(type_str);

        if (strlen(mechs[i].assigned_pilot) > w_pilot)
            w_pilot = strlen(mechs[i].assigned_pilot);

        if (digits(mechs[i].reactor_power) > w_reactor)
            w_reactor = digits(mechs[i].reactor_power);

        if (digits(mechs[i].armor_health) > w_armor)
            w_armor = digits(mechs[i].armor_health);

        if (digits(mechs[i].ammo) > w_ammo)
            w_ammo = digits(mechs[i].ammo);

		if (strlen(condition_str) > w_condition)
            w_condition = strlen(condition_str);
    }

    printf("+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+\n",
		(int)w_model, "----------------------------------------",
		(int)w_type, "----------------------------------------",
        (int)w_reactor, "----------------------------------------",
        (int)w_armor, "----------------------------------------",
        (int)w_ammo, "----------------------------------------",
        (int)w_pilot, "----------------------------------------",
		(int)w_condition, "----------------------------------------");
    printf("| %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
        (int)w_model, "Model",
		(int)w_type, "Klasa",
        (int)w_reactor, "Moc Reaktora",
        (int)w_armor, "Pancerz",
        (int)w_ammo, "Amunicja",
        (int)w_pilot, "Pilot",
		(int)w_condition, "Stan Techniczny");

    printf("+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+\n",
		(int)w_model, "----------------------------------------",
		(int)w_type, "----------------------------------------",
        (int)w_reactor, "----------------------------------------",
        (int)w_armor, "----------------------------------------",
        (int)w_ammo, "----------------------------------------",
        (int)w_pilot, "----------------------------------------",
		(int)w_condition, "----------------------------------------");

    for (size_t i = 0; i < count; i++) {
		type_str = mech_type_to_str(mechs[i].type);
		condition_str = mech_condition_to_str(mechs[i].condition);
        printf("| %-*s | %-*s | %*d | %*d | %*d | %-*s | %-*s |\n",
            (int)w_model, mechs[i].model,
			(int)w_type, type_str,
            (int)w_reactor, mechs[i].reactor_power,
            (int)w_armor, mechs[i].armor_health,
            (int)w_ammo, mechs[i].ammo,
            (int)w_pilot, mechs[i].assigned_pilot,
			(int)w_condition, condition_str);
    }

	printf("+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+-%.*s-+\n",
		(int)w_model, "----------------------------------------",
		(int)w_type, "----------------------------------------",
        (int)w_reactor, "----------------------------------------",
        (int)w_armor, "----------------------------------------",
        (int)w_ammo, "----------------------------------------",
        (int)w_pilot, "----------------------------------------",
		(int)w_condition, "----------------------------------------");
}