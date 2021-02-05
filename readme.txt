ZAWARTOŚĆ:

Plik heap.cpp zawiera implementację rozszerzonego kopca pozycyjnego w wariancie statycznym.
Plik tree.cpp zawiera implementację drzewa sufiksowego (budowanego na podstawie tablicy sufiksowej).
Plik array.cpp zawiera implementację wyszukiwania wzorców w tekście z użyciem tablicy sufiskowej.

Wszystki 3 struktury działają w czasie O(n) na preprocessing oraz O(m + k) na zapytanie
(ostatnia - O(m + log(n))), gdzie k to liczba wystąpień wzorca w tekście.

Folder data zawiera kilka plików z danymi testowymi.
Skrypt test uruchamia wszystkie 3 implementacje na zadanym pliku z danymi.


UŻYCIE:

Kompilacja - polecenie make.
Format danych - tekst, liczba zapytań, zapytania.
Pliki heap, tree oraz array przyjmują dane na standardowe wejście.
Skrypt test przyjmuje nazwę pliku z danymi.


KOMENTARZE:
Na danych losowych kopiec radzi sobie najgorzej:
	na największym teście: 22s inicjalizacji i średnio 2s na zapytanie przy
	4s/0.0007s na drzewie sufiksowym oraz 15s/0.015 na tablicy sufiksowej.
Na 32. słowie Fibbonacciego kopiec osiągnął 1.4s inicjalizacji i średnio 0.2s na zapytanie
	przy 2.7s/0.0003s na drzewie sufiksowym i 5s/0.009s na tablicy sufiksowej.
