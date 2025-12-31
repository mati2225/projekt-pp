# Planowanie struktury projektu

## Czym ma zajmować się program
- Zarządzanie danymi o mechach
- Przydzielanie pilotów
- Planowanie przeglądów
- Monitorowanie stanu bojowego jednostek

## Dokładny schemat działania programu
...

## Kod żródłowy

| Plik   | Opis   |
| :---   | :----: |
| main.c | Główny plik zawierający punkt wejścia programu (menu oraz wybór) |

## Struktura plików tekstowych

```
model_mecha,klasa_mecha,moc_reaktora,przydzielony_pilot,stan_techniczny
```

struktura "mech":
- model mecha: char model\_mecha[101]
- klasa mecha: enum klasa\_mecha
- moc reaktora: int moc\_reaktora
- przydzielony pilot: char przydzielony\_pilot[51]
- stan techniczny: enum stan\_techniczny

Zestaw cech może być rozszerzony (do dyskusji)
