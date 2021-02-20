							RAPORT

PROBLEM:

Wyszukiwanie wzorca w zadanym wcześniej tekście.


ALGORYTM rozszerzony kopiec pozycyjny:

faza I:
 - wyszukuj kolejne sufiksy tekstu w kolejności rosnącej długości w drzewie trie T:
 	do węzła odpowiadającego maksymalnemu prefiksowi danego sufiksu występującego w T dodaj nowego syna poprzez krawędź etykietowaną kolejną literą sufiksu
 	i w nowym węźle zapamiętaj wskaźnik na aktualny sufiks.
 - jednocześnie utrzymuj drzewo trie P zawierające odwrócone słowa z T.
Dzięki utrzymywaniu trie P fazę I można wykonać w O(n).

faza II:
	Każdy węzeł T zawiera dokładnie 1 wskaźnik na pewien sufiks tekstu. Dla każdego wierzchołka v chcemy wyznaczyć pt[v] - najgłębszy węzeł
	w T odpowiadający prefiskowi sufiksu zapisanego w v. Przetwarzając sufiksy w tej samej kolejności co w fazie I, i korzystając w podobny sposób z drzewa P,
	wyznaczamy te wskaźniki w czasie O(n).
	
zapytanie:
	Utrzymuj zmienną offset := 0. Wyszukaj najgłębszy węzeł będący prefiksem zapytania - w. Kandydatem na wystąpienie zapytania są potomkowie w oraz te sufiksy zapisane
	na ścieżce od korzenia do w, których wskaźnik pt prowadzi do potomka w.
	Następnie utnij prefiks zapytania długości depth[w] i zwiększ offset o depth[w]. Dopóki zapytanie jest niepuste, wykonuj to samo, z tą różnicą,
	że nowo-znajdywani kandydaci już nie są kandydatami na wystąpienie zapytania, a są warunkiem koniecznym, by kandydat znaleziony w 1. iteracji,
	mniejszy o offset od znalezionego w aktualnej iteracji, był faktycznie wystąpieniem zapytania.  


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


TESTY:

banan.in - mały test poprawnościowy
small1.in, small2.in - mały losowy test
big1.in, big2.in, big3.in - większe testy losowe o długości tekstu 8000, 10^6, 8.3 * 10^6 odpowiednio
fib.in - 32. słowo fibbonacciego


czasy podane są w formacie czas w sekundach na inicjalizację / średni czas na zapytanie

test		heap					tree					array

banan.in	6*10^-6 / 4*10^-6		10^-5 / 4*10^-6			10^-5 / 2*10^-6

big1.in		7*10^-3 / 6*10^-4		3*10^-3 / 3*10^-6		4*10^-3 / 2*10^-5

big2.in		2.5 / 0.12				0.6 / 4*10^-5			0.8 / 0.001

big3.in		26.5 / 2.5				4.7 / 7*10^-4			16 / 0.02

fib.in		1.9 / 0.2				2.8 / 4*10^-4			5.4 / 0.009


