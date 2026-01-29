## Wymagania
---
### 1. Wymagania funkcjonalne
1. Reprezentacja danych
- [x] Program musi wykorzystywać typ strukturalny do przechowywania informacji o pojedynczym obiekcie.
- [x] Struktura powinna zawierać pola tekstowe (o określonych maksymalnych długościach) oraz pola liczbowe lub logiczne (zgodnie z tematyką projektu).
- [x] Kolekcja obiektów musi być przechowywana w pamięci typu sterta.
2. Zarządzanie kolekcją obiektów
- [x] Program musi umożliwiać dodawanie nowych obiektów.
- [x] Program musi umożliwiać edycję wybranego obiektu, z uwzględnieniem ewentualnych ograniczeń (np. pola nieedytowalne).
- [-] Program musi umożliwiać usuwanie pojedynczego obiektu oraz usuwanie wielu obiektów spełniających wybrane kryterium.
- [x] Program musi uniemożliwiać usuwanie obiektów, które spełniają określone warunki wykluczające (jeśli przewiduje to temat projektu).
3. Wyszukiwanie i filtrowanie
- [x] Program musi umożliwiać wyszukiwanie obiektów według co najmniej dwóch różnych kryteriów (jednego pola tekstowego i jednego pola liczbowego).
- [x] Wyszukiwanie tekstowe musi umożliwiać dopasowanie pełne lub prefiksowe.
- [x] Wyniki wyszukiwania muszą obejmować wszystkie obiekty spełniające kryteria.
4. Sortowanie
- [x] Program musi umożliwiać sortowanie alfabetyczne według wybranego pola tekstowego.
- [x] Program musi umożliwiać sortowanie według wybranego pola liczbowego.
- [x] Sortowanie może być zrealizowane jako przepisanie danych do nowej struktury z zachowaniem wymaganego porządku - nie ma konieczności przestawiania elementów na strukturze oryginalnej.
- [x] Sortowanie musi działać poprawnie niezależnie od liczby obiektów.
5. Prezentacja danych
- [x] Program musi umożliwiać wyświetlanie pełnej listy obiektów oraz wyników wyszukiwania w formie czytelnych zestawień.
6. Trwałość danych
- [x] Program musi umożliwiać zapis całej kolekcji obiektów do pliku tekstowego lub binarnego.
- [x] Program musi umożliwiać odczyt danych z pliku i odtworzenie kolekcji obiektów w pamięci.
- [x] Program musi obsługiwać błędy związane z plikami (brak pliku, niezgodny format, przerwane dane) w sposób kontrolowany.
- [x] Ścieżki/nazwy plików używane do zapisu/odczytu muszą być przekazywane jako parametry wywołania programu.
### 2. Wymagania niefunkcjonalne
1. Jakość kodu
- [x] Kod programu musi być modularny, a funkcje logicznie rozdzielone zgodnie z odpowiedzialnościami.
- [x] Program musi być podzielony na pliki źródłowe i nagłówkowe, zgodnie z zasadami modularności w C.
- [x] Program musi wykorzystywać bezpieczne funkcje wejścia-wyjścia, walidować dane wejściowe oraz unikać przepełnień buforów.
- [x] Program musi unikać wycieków pamięci i niepoprawnych operacji na wskaźnikach.
2. Interfejs użytkownika
- [x] Interfejs programu musi być oparty na czytelnym, intuicyjnym menu tekstowym obejmującym wszystkie funkcje systemu.
- [x] Komunikaty programu muszą być jednoznaczne, zrozumiałe i informować użytkownika o błędach oraz sposobach ich rozwiązania.
3. Niezawodność
- [x] Program nie może kończyć działania na skutek błędnego wejścia; wszystkie takie sytuacje muszą być obsługiwane komunikatami i ponawianiem operacji.
- [x] Program musi działać stabilnie dla kolekcji liczącej co najmniej kilkaset obiektów.

