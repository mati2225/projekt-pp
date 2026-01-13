# Planowanie struktury projektu

## Czym ma zajmować się program
- Zarządzanie danymi o mechach
- Przydzielanie pilotów
- Planowanie przeglądów
- Monitorowanie stanu bojowego jednostek

## Dokładny schemat działania programu
1. Uruchomienie programu (oraz podanie sciezki do pliku)
2. Wczytanie danych z pliku do listy
3. Operacje na danych wczytanych z pliku do listy, poprzez wybor opcji w menu
4. Zapisanie zmodyfikowanych danych z listy do pliku

## Menu
1. Dodaj nowego mecha
2. Edytuj wybrana jednostke
    - Zmien klase mecha
    - Zwieksz moc reaktora
    - Zmniejsz moc reaktora
    - Napraw pancerz
    - Uzupelnij amunicje
    - Przydziel pilota
    - Zmien stan techniczny
    - Usun jednostke z ewidencji
3. Wyswietl informacje o wybranej jednostce
4. Wyswietl wszystkie jednostki
    - wyswietlenie wszystkich jednostek z mozliwoscia posegregowania wynikow
0. Zakoncz dzialanie programu 

## Struktura plików tekstowych

```
model_mecha,klasa_mecha,moc_reaktora,armor_health,ammo,przydzielony_pilot,stan_techniczny
```

struktura "mech":
- model mecha: char model\_mecha[101]
- klasa mecha: enum klasa\_mecha
- moc reaktora: int moc\_reaktora
- poziom uzbrojenia: int armor_health
- poziom amunicji: int ammo
- przydzielony pilot: char przydzielony\_pilot[51]
- stan techniczny: enum stan\_techniczny

Zestaw cech może być rozszerzony (do dyskusji)
