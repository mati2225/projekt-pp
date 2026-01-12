# projekt-pp - Projekt na zaliczenie Podstaw Programowania

## Informacje o projekcie:
###  Wybrany temat: 4. Zarządzanie flotą Mechów Bojowych
### Autorzy projektu:
- [Mateusz Tomczuk](https://github.com/mati225)
- [Michał Zwierzyński](https://github.com/Miyotaka727)
- [Kuba Kirej](https://github.com/KubaKSalony334)

## Treść zadania (tymczasowo):

### 4. Zarządzanie flotą Mechów Bojowych

W roku 2264 wojny prowadzone są nie przez klasyczne armie, lecz przez pilotów sterujących gigantycznymi mechami bojowymi. Każdy z tych potężnych egzomechów wyposażony jest w zaawansowany reaktor, systemy uzbrojenia, pancerze i moduły specjalne. Ich wartość jest ogromna, a utrata choć jednego z nich może zaważyć na wyniku całej kampanii militarnej.

Aby utrzymać flotę w pełnej gotowości bojowej, powstał centralny system ewidencji mechów. Twoim zadaniem jest stworzenie programu umożliwiającego zarządzanie danymi o mechach. System ma wspierać oficerów technicznych w przydzielaniu pilotów, planowaniu przeglądów i monitorowaniu stanu bojowego jednostek.

Każdy mech posiada minimalny (może być rozszerzony) zestaw cech, które muszą zostać zapisane w systemie:
- model mecha - unikalna nazwa modelu, o maksymalnej długości 100 znaków. Pełni funkcję identyfikatora jednostki i nie może być zmieniana po rejestracji;
- klasa mecha - określenie taktycznej roli jednostki, np.: szturmowy, wsparcia ogniowego, rekonesansowy, obronny;
- moc reaktora - wartość liczbowa określająca maksymalną moc generowaną przez reaktor (np. w MW). Wysokość tej wartości wpływa na możliwości bojowe jednostki. Sugerowana wartości <0, 100>
- przydzielony pilot - nick pilota aktualnie przypisanego do mecha. Jeżeli jednostka pozostaje bez pilota, pole może być puste;
- stan techniczny - opis aktualnego stanu mecha: sprawny, uszkodzony, w naprawie, wymaga przeglądu. Mech może zostać wycofany z ewidencji wyłącznie wtedy, gdy znajduje się oficjalnie w stanie demontażu lub naprawy. Jednostki aktywne, uszkodzone czy przypisane do misji nie mogą być usuwane. Program powinien uniemożliwić usunięcie takiego wpisu i wyświetlić odpowiedni komunikat.

