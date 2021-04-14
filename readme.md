# AISD zadania opis

## dokumentacja

dokumentację projektu można znaleźć na <https://kamkamkil.github.io/graph_algorithms/index.html>

## instalacja

### linux

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

### windows

na początku musimy mieć zainstalowany program cmake. Jeżeli mamy packet Manager choco możemy zainstalować cmake za jego pomocą:

```bash
choco install cmake
```

jeżeli nie korzystamy z choco możemy prosto zainstalować cmake [tutaj](https://cmake.org/download/) należy pamiętać aby dodać go jako zmienną środowiskową.

następnie musimy utworzyć plik built (np `mkdir build`) i w nim wpisujemy `cmake ..`, a następnie wpisujemy  `cmake --build .`

### tylko uruchomienie testów

Jeżeli chcemy tyko sprawdzić czy testy poprawnie są wykonywane możemy będąc w pliku build wpisać `ctest` (działa po skompilowaniu programu, logi pojawią się w pliku build)

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

## Zadanie ciekawe 1: przemytnicy

### uruchomienie programu

Po [skompilowaniu rozwiązania](#instalacja) (nazywa się przemytnicy) uruchamiamy program przysyłając do niego nazwę pliku tekstowego z danymi jakie chcemy wprowadzić

### sposób rozumowania

Ten problem można przedstawić w następujący sposób: szukamy takiego cyklu prostego przechodzącego przez konkretny wierzchołek która będzie najkrótsza wedle następującej metryki: suma długości krawędzi plus połowa wartości najtańszego wierzchołka problem ten można rozwiązać szukając wszystkich cykli prostych i następnie sprawdzić który z nich jest najkrótszy lub zastosować podobny algorytm do algorytmu Dijkstry.  

### naiwny sposób rozumowania

w naiwnym sposobie rozumowania na początku szukamy wszystkich pętli a następnie wybieramy tą najtańszą

1. Stwórz wektor wektorów V i włóż do niego wektor zawierający wierzchołek 0

2. Dla każdego wektora(V') w wektorze V znajdź sąsiadów wierzchołka znajdującego się na końcu wektora

3. Jeżeli wierzchołek ma:

    a. 0 sąsiadów: jeżeli ostatni wierzchołek jest inny niż 0 to dodaj ten wektor do listy wektorów do usunięcia

    b. 1 sąsiada: jeżeli ten sąsiedni wierzchołek jest różny od wierzchołka 0 dodaj do tego wektora V' jego sąsiada

    c. jeżeli ma więcej niż jednego sąsiada: dla każdego sąsiada nie będącego 0 utwórz kopie wektora V' i dodaj na koniec tego sąsiada, dodaj oryginał do listy do usunięcia

4. Usuń z wektora elementy z listy do usunięcia (należy to robić w malejącej kolejności żeby nie invalidować tej listy)

5. Powtarzaj punkty 2 - 4 aż w pętli nie zmodyfikujesz wektora V

Następnie dla każdej pętli liczymy jej długość zliczając sumę długości krawędzi oraz dodając do niej połowę najtańszej wartości wierzchołka, do naszego wektora cen warto dodać jeszcze połowę ceny wierzchołka 0 na wypadek jakby to była najbardziej opłacalna trasa

### limitację rozwiązania naiwnego

Implementacja mojego rozwiązania na pewno nie jest idealna wektory V' które na pewno nie będą już dalej rozwijane dalej są brane pod uwagę (powinny zostać przeniesione do innego zbioru) do tego w przypadku 3a zamiast usuwać i dodawać wektory powinniśmy wykorzystać jeden już istniejący. Poza tym w mojej implementacji grafu szukanie sąsiadów jest dość kosztownę więc przechowywanie wcześniej obliczonych wartość np. w mapie również poprawiło by wydolność programu. Dodatkowo test "many_dead_ends" ujawnił że algorytm podstawowy nie zawsze usuwa wszystkie niepoprawne cykle.

### (bardziej) optymalne rozwiązanie

w (bardziej) optymalnym rozumowaniu zamiast szukać każdej z pęli po kolei w każdej iteracji algorytmu wybieramy najtańszą opcję:

przyjmujemy punkt startu current = 0

1. Stwórz wektor wektorów V i włóż do niego wektory w postaci {0,n} gdzie n to sąsiedzi wierzchołka 0

2. sprawdzamy czy ostatni wierzchołek to punkt 0 jeżeli tak to przenosimy ten cykl do wektora full pt: 4

3. wyszukujemy sąsiadów ostatniego wierzchołka pętli jeżeli ma

    a. 0 sąsiadów to oznacza nie przeszukujemy teraz pętli, więc usuwamy tą pętle

    b. 1.sąsiada to jeżeli jest to dodajemy go do pętli

    c. > 1 sąsiadów to tworzymy kopię aktualnego cyklu i na koniec tych kopii dodajemy ten wieszchołek dla każdego sąsiada poza jednym którego zostawiamy aby dodać go do aktualnego cyklu (nie musimy wtedy usuwać nic z wektora)

4. następna pętla nad którą pracujemy to taka która ma najmniejszy całkowity koszt

5. wracamy teraz do pk 2 z cyklem current wybranym z poprzednim punkcie chyba że zostanie spełniony jeden z warunków stopu:

    a. wszystkie poprawne cykle zostały w pełni rozpoznanę w tedy musimy przeszukać tą listę i wybrać najtańszą opcję

    b. najtańsza opcja z listy pełnych cykli jest nie droższa niż najtańsza opcja bez ceny zamiany z wektora V (robimy ponieważ wtedy dla każdej nie zerowej ceny zamiany inne opcje będą droższe) - to można jeszcze zoptymalizować [patrz](#jeszcze-większa-optymalizacja)

6. na koniec musimy jeszcze sprawdzić czy cena zamiany wierzchołka 0 nie jest tańsza niż cena naszej pętli

### złożoność   obliczeniowa

Algorytm w najgorszej opcji musi znaleźć wszystkie pętle wychodzące z wierzchołka 0 co oznacza że musimy przeszukać nasz graf DFS co oznacza O(E + V) dodatkowo pod koniec każdej iteracji musimy wykonać test które będą zależały od ilość aktualnie znanych cyklów.

### złożoność   pamięciowa

potrzeba odpowiednią ilość pamięci na graf: O(V^2 + V) int, dodatkowo potrzeba miejsca na przetrzymywanie miejsca na cykle, każdy cykl ma maksymalnie O(V) wierzchołków w sobie a takich cyków może być maksymalnie O(E) (sytuacja kiedy jeden cykl od 0 do 0) czyli w sumie O(VE)

### porównanie wydolności algorytmu naiwnego i wydajniejszego

przygotowałem prosty benchmark który ma za zadanie porównać wydolność algorytmów sprawdzamy go na 2 przypadkach: pierwszym który jest przykładem z zadania w którym oba algorytmy muszą wykonać podobną pracę ponieważ należy sprawdzić cały graf aby znaleźć odpowiednią pętle oraz ciężki który ma jedną tanią trasę i wiele bardzo drogich, naiwny algorytm musi przeszukać je wszystkie a wydajnieszy kończy prace po znalezieniu taniej pętli. Aby go uruchomić można uruchomić program  `benchmarkPrzemytnicy` albo użyć `ctest` wtedy wynik pojawi się w logach znajdujących się w pliku build.

#### wyniki benchmarku

```bash
-------------------------------------------------------------------------------
benchmark_easy
-------------------------------------------------------------------------------

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
naiveAlgorithm                                 100             4    21.8828 ms 
                                        53.4464 us    52.7004 us    55.3936 us 
                                        5.70498 us    2.64138 us    11.7936 us

betterAlgorithm                                100             4     23.482 ms 
                                        56.9374 us    55.0001 us    61.9646 us 
                                        14.7598 us    6.76637 us    29.8458 us


-------------------------------------------------------------------------------
benchmark_hard
-------------------------------------------------------------------------------

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
naiveAlgorithm                                 100             2    40.7802 ms 
                                        197.446 us    191.964 us    206.791 us 
                                        35.8081 us    23.3096 us    53.3342 us

betterAlgorithm                                100             2    23.1002 ms 
                                        110.509 us    108.922 us    114.048 us 
                                        11.4989 us    6.39255 us    22.4014 us

```

jak widać po wynikach dla prostego przykładu różnicy nie ma a nawet lepszy algorytm może być mniej wydajny a w przypadku mniej korzystnego na naiwnego algorytmu przykładu rożnica potrafi być nawet dwukrotna (wyniki oczywiście będą się różnić w zależności od systemu)

### dodatkowe uwagi

#### wyjście z pętli

jeżeli w grafie jest pętla która nie zawiera wierzchołka 0 nie ma jawnego sposobu w jaki algorytm zatrzymuje dodawanie tych wierzchołków w kółko jednak ta trasa w pewnym momencie dłuższa od pozostałych możliwości więc na pewno algorytm się skończy. Można by było jawnie sprawdzać czy na pewno wierzchołek został nie został już odwiedzony w tej pętli ale podjąłem decyzje że taka taka sytuacja będzie występować żadziej więc dodatkowe sprawdzanie średnio wydłużyło by czas trwania algorytmu.

#### przypadek w którym samo złoto jest "najtańsze"

Jak w powyższym przypadku można by było w każdej iteracji sprawdzać czy złoto nie jest tańszą opcją ale jako że taka sytuacja nie będzie występować często podjąłem decyzję aby sprawdzać taki przypadek dopiero na końcu

#### jeszcze większa optymalizacja

nasz algorytm zakłada że dodatkowy koszt zmiany jest nam nie znany, jednak można by było sprawdzać jaki jest najtańszy koszt zmiany i jego użyć w różnicy przy warunku wyjścia, wtedy algorytm w niektórych sytuacjach kończyłby się wcześniej

## zadanie ciekawe 2: skarbonka

### sposób  rozumowania

W tym zadania należy zauważyć że w grafie wierzchołki mogą mieć inny wierzchołek który na nie wskazuje lub nie, możemy również zauważyć że poza pętlami kiedy będziemy się "cofać" to zawsze znajdziemy wierzchołek na który nie wskazuje żaden inny to od tych powinniśmy zacząć analizę następnie przetestować inne.

### Opis  algorytmu

1. Dla każdego wierzchołka n na którego nie skazuje żaden inny wierzchołek (przy każdej iteracji zwiększamy licznik )

    a. zaznacz wierzchołek n jako odwiedzony

    b. jeżeli ma sąsiadów to ustaw jako n jego sąsiada (z treści zadania możemy wnioskować że każdy wierzchołek ma tylko jednego sąsiada)

    c. jeżeli wierzchołek niema sąsiada lub natrafimy na odwiedzonego wcześniej wierzchołka kończymy pętle inaczej wracamy do punktu 1a

2. dla każdego nie odwiedzonego wcześniej wierzchołka robimy punkty a - c, również zwiększając licznik.

### Złożoność  Pamięciowa

do tego algorytmu potrzebujemy znać nasz graf  O(V^2 + V) (w tym przypadku lepiej było by użyć grafu zdefiniowanego jako list sąsiedztwa w tedy złożoność wynosiłaby O(V) ponieważ każdy wierzchołek ma tylko jednego sąsiada) oraz wektor wierzchołków odwiedzonych O(V)

### złożoność obliczeniowa

Musimy odwiedzić każdy wierzchołek jeden raz więc złożoność wynosi O(V), ale jako że złożoność znajdowania sąsiadów którą musimy wykonać dla każdego wierzchołka wynosi O(V), oraz złożoność szukania poprzedników również jest O(V) złożoność całego algorytmu wraz dostępem do danych grafu wynosi O(V^3) użycie grafu w postaci listy sąsiedztwa zredukował by to do O(v^2)

### wersja "zoptymalizowana"

oryginalna wersja `skarbonkaNaive` nie ma wcześniejszego warunku stopu, zawsze sprawdza wszystkie wierzchołki do których możemy się dostać z tego nad którym teraz pracujemy, polepszona wersja `skarbonka` ma wcześniejszy warunek stopu tego testu. To powinno poprawić poprawić wydajność w sytuacjach których mamy długą linię wierzchołków i wiele pojedynczych które w nią celują.

### benchmark

```bash
-------------------------------------------------------------------------------
simple_example
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
naive_algorithm                                100             2    28.0008 ms 
                                        150.097 us     140.16 us    162.373 us 
                                        55.9958 us    46.9952 us    65.6539 us

improved_algorithm                             100             9    26.3799 ms 
                                        26.9756 us    26.3907 us    28.4913 us 
                                         4.3846 us    1.39188 us    8.45691 us


-------------------------------------------------------------------------------
harder_benchark
...............................................................................

benchmark name                       samples       iterations    estimated
                                     mean          low mean      high mean
                                     std dev       low std dev   high std dev
-------------------------------------------------------------------------------
naive algorithm                                100             1    109.385 ms 
                                        1.08904 ms    1.07599 ms    1.10949 ms 
                                        81.9418 us    59.1273 us    119.447 us

improved_algorithm                             100             3    30.6591 ms 
                                        107.138 us    105.225 us    109.915 us 
                                        11.6243 us    8.68783 us    16.1308 us
```

Jak widać polepszona wersja nawet 10 razy bardziej wydajna, nawet w przykładnie który nie powinien dawać mu zdecydowanej przewagi, najprawdopodobniej jest to spowodowane tym że algorytm DFS musi dodatkowo przygotowywać pamięć i wykonywać dodatkowe akcję których nie musi wykonywać lepszy algorytm
