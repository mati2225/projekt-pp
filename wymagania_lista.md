## Wymagania
---
### 1. Wymagania funkcjonalne
1. Reprezentacja danych
- [ ] Program musi wykorzystywać typ strukturalny do przechowywania informacji o pojedynczym obiekcie.
- [ ] Struktura powinna zawierać pola tekstowe (o określonych maksymalnych długościach) oraz pola liczbowe lub logiczne (zgodnie z tematyką projektu).
- [ ] Kolekcja obiektów musi być przechowywana w pamięci typu sterta.
2. Zarządzanie kolekcją obiektów
- [ ] Program musi umożliwiać dodawanie nowych obiektów.
- [ ] Program musi umożliwiać edycję wybranego obiektu, z uwzględnieniem ewentualnych ograniczeń (np. pola nieedytowalne).
- [ ] Program musi umożliwiać usuwanie pojedynczego obiektu oraz usuwanie wielu obiektów spełniających wybrane kryterium.
- [ ] Program musi uniemożliwiać usuwanie obiektów, które spełniają określone warunki wykluczające (jeśli przewiduje to temat projektu).
3. Wyszukiwanie i filtrowanie
- [ ] Program musi umożliwiać wyszukiwanie obiektów według co najmniej dwóch różnych kryteriów (jednego pola tekstowego i jednego pola liczbowego).
- [ ] Wyszukiwanie tekstowe musi umożliwiać dopasowanie pełne lub prefiksowe.
- [ ] Wyniki wyszukiwania muszą obejmować wszystkie obiekty spełniające kryteria.
4. Sortowanie
- [ ] Program musi umożliwiać sortowanie alfabetyczne według wybranego pola tekstowego.
- [ ] Program musi umożliwiać sortowanie według wybranego pola liczbowego.
- [ ] Sortowanie może być zrealizowane jako przepisanie danych do nowej struktury z zachowaniem wymaganego porządku - nie ma konieczności przestawiania elementów na strukturze oryginalnej.
- [ ] Sortowanie musi działać poprawnie niezależnie od liczby obiektów.
5. Prezentacja danych
- [ ] Program musi umożliwiać wyświetlanie pełnej listy obiektów oraz wyników wyszukiwania w formie czytelnych zestawień.
6. Trwałość danych
- [ ] Program musi umożliwiać zapis całej kolekcji obiektów do pliku tekstowego lub binarnego.
- [ ] Program musi umożliwiać odczyt danych z pliku i odtworzenie kolekcji obiektów w pamięci.
- [ ] Program musi obsługiwać błędy związane z plikami (brak pliku, niezgodny format, przerwane dane) w sposób kontrolowany.
- [ ] Ścieżki/nazwy plików używane do zapisu/odczytu muszą być przekazywane jako parametry wywołania programu.
### 2. Wymagania niefunkcjonalne
1. Jakość kodu
- [ ] Kod programu musi być modularny, a funkcje logicznie rozdzielone zgodnie z odpowiedzialnościami.
- [ ] Program musi być podzielony na pliki źródłowe i nagłówkowe, zgodnie z zasadami modularności w C.
- [ ] Program musi wykorzystywać bezpieczne funkcje wejścia-wyjścia, walidować dane wejściowe oraz unikać przepełnień buforów.
- [ ] Program musi unikać wycieków pamięci i niepoprawnych operacji na wskaźnikach.
2. Interfejs użytkownika
- [ ] Interfejs programu musi być oparty na czytelnym, intuicyjnym menu tekstowym obejmującym wszystkie funkcje systemu.
- [ ] Komunikaty programu muszą być jednoznaczne, zrozumiałe i informować użytkownika o błędach oraz sposobach ich rozwiązania.
3. Niezawodność
- [ ] Program nie może kończyć działania na skutek błędnego wejścia; wszystkie takie sytuacje muszą być obsługiwane komunikatami i ponawianiem operacji.
- [ ] Program musi działać stabilnie dla kolekcji liczącej co najmniej kilkaset obiektów.

