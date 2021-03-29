# AISD zadania opis

## zad 5 topologiczne sortowanie wierzchołków

### opis algorytmu

algorytm działa na zmodyfikowanym algorytmie DFS, przygotowany w taki sposób aby zapamiętywał i wracał do wcześniej odwiedzonych wierzchołków, kiedy odwiedzi wierzchołek który nie ma już wychodzących krawędzi lub którego wszystkich sąsiadów odwiedziliśmy dodajemy go na koniec wektora. W tym algorytmie zgodnie z poleceniem zakładamy że graf nie ma żadnych cykli i nie sprawdzamy czy je ma, danie nie poprawnego grafu może przynieść nie oczekiwane rezultaty.

### opis testów

W teście sprawdzamy nasz algorytm na dwóch przypadkach, mniejszym i większym grafie. Po posortowaniu topologicznie wierzchołków po kolei, dla każdego wierzchołka przechodzimy przez graf DFS i sprawdzamy czy znalezione wierzchołki znajdują się przed aktualnie sprawdzanym wierzchołkiem w zbiorze posortowanych, jeżeli nie to nasz algorytm działa poprawnie.

### Złożoność  obliczeniowa

dla każdego wierzchołka musimy znaleźć wszystkich jego sąsiadów dla k wierzchołków i dla algorytmu szukania sąsiadów który jest o(k) mamy złożoność o(k^2) warto jeszcze dodać że moja implementacja nie jest idealnie zoptymalizowana, przy powrocie do odwiedzonych już wierzchołków ponownie szukamy ich sąsiadów co dla wielkich grafów może zdecydowanie spowolnić algorytm. Rekurencyjna opcja tego algorytmy (choć też nie koniecznie idealna po wezwanie rekurencji nie było by na końcu więc kompilator nie koniecznie byłby w stanie ją rozwinąć) lub zapisywanie sąsiadów (tutaj znowu wzrosła by złożoność pamięciowa) zniwelowały by ten problem, reprezentacja grafu za pomocą listy sąsiedztwa również by pomogła (zakładając że tam możemy dostać listę sąsiadów w o(1))

### złożoność pamięciowa

Sam algorytm (nie licząc grafu) do pracy wymaga :

- wektora bool o długości k (ilość wierzchołków)

- wektora size_t o długości k

- stosu size_t o maksymalnej długości k

- wektora size_t o maksymalnej długości w (ilość krawędzi)

- oraz kilku zmiennych pomocniczych

size_t w c++ ma wielkość co najmniej 16 bitów, tyle też przyjmę, zakładam tez że stos jak i wektor to wydzielony blok pamięci o danej długości w takim przypadku złożoność to k * 1 + k * 16 + k * 16 + w * 16 = k * 33 + w * 16