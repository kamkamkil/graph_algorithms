# AISD zadania opis

## dokumentacja

dokumentację projektu można znaleźć na <https://kamkamkil.github.io/graph_algorithms/index.html>

## instalacja

do kompilacji programu wymagany jest program cmake,aby zainstalować make należy wpisać:

```bash
sudo apt  install cmake
```

następnie należy utworzyć folder build:

```bash
mkdir build
```

następnie wchodzimy do pliku build

```bash
cd build
```

teraz za pomocą cmake przygotowujemy konfigurację naszego projektu, cmake powinien znaleźć nasz kompilator i przygotować nam makefile

```bash
cmake ..
```

teraz mamy już wygenerowany naż makefile, wystarczy wpisać make i nasz program zostanie skompilowany, pliki wykonywalne będą znajdować się w folderze build.

Jeżeli chcemy tyko sprawdzić czy testy poprawnie są wykonywane możemy będąc w pliku build wpisać `ctest` (działa po skompilowaniu programu)

## zad 5 topologiczne sortowanie wierzchołków

### opis algorytmu

algorytm działa na zmodyfikowanym algorytmie DFS, przygotowany w taki sposób aby zapamiętywał i wracał do wcześniej odwiedzonych wierzchołków, kiedy odwiedzi wierzchołek który nie ma już wychodzących krawędzi lub którego wszystkich sąsiadów odwiedziliśmy dodajemy go na koniec wektora. W tym algorytmie zgodnie z poleceniem zakładamy że graf nie ma żadnych cykli i nie sprawdzamy czy je ma, danie nie poprawnego grafu może przynieść nie oczekiwane rezultaty.

### opis testów

W teście sprawdzamy nasz algorytm na dwóch przypadkach, mniejszym i większym grafie. Po posortowaniu topologicznie wierzchołków po kolei, dla każdego wierzchołka przechodzimy przez graf DFS i sprawdzamy czy znalezione wierzchołki znajdują się przed aktualnie sprawdzanym wierzchołkiem w zbiorze posortowanych, jeżeli nie to nasz algorytm działa poprawnie.

### Złożoność  obliczeniowa

dla każdego wierzchołka musimy znaleźć wszystkich jego sąsiadów dla k wierzchołków i dla algorytmu szukania sąsiadów który jest o(k) mamy złożoność o(k^2)

<!-- warto jeszcze dodać że moja implementacja nie jest idealnie zoptymalizowana, przy powrocie do odwiedzonych już wierzchołków ponownie szukamy ich sąsiadów co dla wielkich grafów może zdecydowanie spowolnić algorytm. Rekurencyjna opcja tego algorytmy (choć też nie koniecznie idealna po wezwanie rekurencji nie było by na końcu więc kompilator nie koniecznie byłby w stanie ją rozwinąć) lub zapisywanie sąsiadów (tutaj znowu wzrosła by złożoność pamięciowa) zniwelowały by ten problem, reprezentacja grafu za pomocą listy sąsiedztwa również by pomogła (zakładając że tam możemy dostać listę sąsiadów w o(1)) -->

### złożoność pamięciowa

Sam algorytm (nie licząc grafu) do pracy wymaga :

- wektora bool o długości k (ilość wierzchołków)

- wektora size_t o długości k

- stosu size_t o maksymalnej długości k

- wektora size_t o maksymalnej długości w (ilość krawędzi)

- oraz kilku zmiennych pomocniczych

size_t w c++ ma wielkość co najmniej 16 bitów, tyle też przyjmę, zakładam tez że stos jak i wektor to wydzielony blok pamięci o danej długości w takim przypadku złożoność to k * 1 + k * 16 + k * 16 + w * 16 = k * 33 + w * 16

## zad 7 szukanie cyklu w grafie

### Opis Algorytmu

Moją implementacje Algorytmu szukania cyklu w grafie można podzielić na dwa etapy w pierwszym etapie sprawdzamy czy graf ma pętlę a w drugim "czyścimy stos". Pierwszy polega na przeszukaniu grafu algorytmem DFS i sprawdzaniem czy z danego elementu możemy wrócić do niego samego. Później usuwamy z stosu elementy nie należące do naszej cyklu: idąc po kolej od ostatniego elementu do pierwszego sprawdzamy czy z poprzedniego można dojść do następnego jeżeli nie do usuwamy go z stosu. Sprawdzanie czy cykl jest graf jest Hamiltonoski polega na porównaniu długości cyklu i ilość wierzchołków w grafie, sprawdzenie czy cykl jest Euleroski polega na sprawdzeniu czy długość cyklu jest równa ilość krawędzi grafu (ten test jest wystarczający ponieważ algorytm wyszukuje tylko cykle proste więc jego długość jest równo ilość krawędzi jaką zawiera)

### Opis testów

Testy do tego algorytmu polegają na podaniu danych o różnej złożoności i dosłownym sprawdzeniu czy wyniki się zgadzają, możemy tak zrobić ponieważ funkcję można uznać za "czystą" tzn. że dla tych samych danych zawsze da nam ten sam wynik. Jeżeli nie znalibyśmy dobrego wyniku i chcielibyśmy sprawdzić poprawność naszego algorytmu moglibyśmy sprawdzić czy kolejne elementy cyklu są swoimi sąsiadami oraz czy pętla jej poprawna (ostatni element jest sąsiadem pierwszego).

### Złożoność obliczeniowa

Algorytm można podzielić na dwie części : sprawdzenie czy graf ma pętlę polega na wywołaniu przeszukiwania DFS w najgorszym wypadku na każdym elemencie (złożoność O(V + E) (v - ilość wierzchołków E - ilość krawędzi)). Do "wyczyszczenia" Stosu musimy wywołać sprawdzeni sąsiadów na każdym z elementów cyklu więc będzie to O(V^2), ponieważ w najgorszym przypadku cykl ma V elementów a w mojej implementacji grafu szukanie sąsiadów ma złożoność V.

### Złożoność pamięciowa

Do wykonania algorytmu potrzebujemy stosu size_t o max rozmiarze długości stosu (16 bit \* V) wektora odwiedzonych wierzchołków typu size_t (16 bit \* V) oraz wektora wierzchołków odwiedzonych globalnie (1 bit \* V).Do Czyszczenia potrzebujemy jeszcze wektora size_t który jest silnie mniejszy od ilości wierzchołków (16 bit \* V). W sumie O( 49 bit \* V ).

## zad 10 domknięcie przechodnie liczone metodą Floyda-Warshalla

### opis  algorytmu

algorytm jest bardzo podobny do algorytmu Floyda-Warshalla tutaj jednak zamiast arytmetycznie dodawać odległości robimy to logicznie.

### Opis Testów

testy polegają na użyciu DFS aby sprawdzić wszystkie możliwe wierzchołki do których można się dostać

### Złożoność  Obliczeniowa

linia kodu:

```c++
result[i][j] = result[i][j] || (result[i][a] && result[a][j]);
```

musi być wykonana k^3 razy gdzie k to ilość wierzchołków. warto jeszcze dodać że musimy "odkryć wszystkich sąsiadów wierzchołków startowych co jest k^2. Ostateczna złożoność obliczeniowa to o(k^3)

### złożoność Pamięciowa

potrzebujemy macierzy bool k na k więc złożoność pamięciowa to o(k^2)

## Zadanie dodatkowe 1: przemytnicy

### sposób rozumowania

Ten problem można przedstawić w następujący sposób: szukamy takiego cyklu prostego przechodzącego przez konkretny wierzchołek która będzie najkrótsza wedle następującej metryki: suma długości krawędzi plus połowa wartości najtańszego wierzchołka problem ten można rozwiązać szukając wszystkich cykli prostych i następnie sprawdzić który z nich jest najkrótszy lub zastosować podobny algorytm do algorytmu Dijkstry.  
Jak zastosowałem pierwszą metodę czyli znalazłem wszystkie cykle przechodzące przez wierzchołek zerowy i wybrałem najtańszą opcję, zrobiłem to w następujący sposób

1. Stwórz wektor wektorów V i włóż do niego wektor zawierający wierzchołek 0

2. Dla każdego wektora(V') w wektorze V znajdź sąsiadów wierzchołka znajdującego się na końcu wektora

3. Jeżeli wierzchołek ma:

    a. 0 sąsiadów: jeżeli ostatni wierzchołek jest inny niż 0 to dodaj ten wektor do listy wektorów do usunięcia

    b. 1 sąsiada: jeżeli ten sąsiedni wierzchołek jest różny od wierzchołka 0 dodaj do tego wektora V' jego sąsiada

    c. jeżeli ma więcej niż jednego sąsiada: dla każdego sąsiada nie będącego 0 utwórz kopie wektora V' i dodaj na koniec tego sąsiada, dodaj oryginał do listy do usunięcia

4. Usuń z wektora elementy z listy do usunięcia (należy to robić w malejącej kolejności żeby nie invalidować tej listy)

5. Powtarzaj punkty 2 - 4 aż w pętli nie zmodyfikujesz wektora V

Następnie dla każdej pętli liczymy jej długość zliczając sumę długości krawędzi oraz dodając do niej połowę najtańszej wartości wierzchołka, do naszego wektora cen warto dodać jeszcze połowę ceny wierzchołka 0 na wypadek jakby to była najbardziej opłacalna trasa

```c

W zależności kiedy pan to będzie czytał niektóre z tych limitacji może będą już poprawionę 

```

### limitację rozwiązania

Implementacja mojego rozwiązania na pewno nie jest idealna wektory V' które na pewno nie będą już dalej rozwijane dalej są brane pod uwagę (powinny zostać przeniesione do innego zbioru) do tego w przypadku 3a zamiast usuwać i dodawać wektory powinniśmy wykorzystać jeden już istniejący. Poza tym w mojej implementacji grafu szukanie sąsiadów jest dość kosztownę więc przechowywanie wcześniej obliczonych wartość np. w mapie również poprawiło by wydolność programu. Dodatkowo test "many_dead_ends" ujawnił że algorytm podstawowy nie zawsze usuwa wszystkie niepoprawne cykle.
