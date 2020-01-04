# Projekt Analiza Algorytmów

## Wizytówka

| Pole      | Wartość       |
| --------- |:-------------:|
| Imię      | Wojciech      |
| Nazwisko  | Sitek         |
| Numer indeksu | 293148 |
| Studia | Informatyka inżynierskie |
| Semestr | 5 |

## Tytuł i treść problemu
### Przepustowość

Dany jest graf opisujący pewną sieć wodociągową, w którym wierzchołki są oznaczone jako zawory, źródła lub punkty odbioru. Każdy zawór może być ustawiony na przepustowość w zakresie [0,1], każde źródło ma określoną wydajność, a odcinek stałą przepustowość w zakresie [0,1].
Opracować algorytm, który dla danych nastaw zaworów określi ilość wody docierającej do wszystkich punktów odbioru.

## Informacja o możliwych poleceniach aktywacji programu
### Kompilacja

### Warianty uruchomienia
- Rozwiąż zadany graf `./solve [resultsFileName] [>graphFileName]`
    - Wpisz dane ręcznie lub przekieruj z pliku.
    - Wypisz dane tylko na standardowe wyjście lub także do pliku (nazwa pliku jako argument).
- Wygeneruj i sprawdź graf o zadanych atrybutach `./generate generatedGraphOutputFile solvedResultsOutputFile sourceCount valveCount receiverCount augmentingPathCount averageAugmentingPathLength augmentingPathLengthStandardDeviation`
- Wygeneruj i sprawdź poprawność i czas wykonania `./solve_tester outputFile startValveCount iterationCount`
    - Polecane argumenty to `tester.txt 100 500`
    - Inne atrybuty generatora są ustawiane w zależności od tych dwóch
- Wygeneruj i sprawdź czasy wykonania przy zwiększanej szybko ilości zaworów `./valve_profiler outputFile startValveCount iterationCount`
    - Polecane argumenty to `zawory.txt 1000 5000`
    - Inne atrybuty generatora są ustawiane w zależności od tych dwóch
- Wygeneruj i sprawdź czasy wykonania przy zwiększanej szybko ilości odcinków `./edge_profiler outputFile startValveCount iterationCount`
    - Polecane argumenty to `odcinki.txt 1000 5000`
    - Inne atrybuty generatora są ustawiane w zależności od tych dwóch
- Narysuj wykres złożoności `python3 plot.py fileName`
    - parametr `fileName` to nazwa pliku wygenerowanego przez solve_tester, valve_profiler lub edge_profiler
## Opis konwencji dotyczących danych wejściowych i prezentacji wyników
### Dane wejściowe
```
[source count]  
[valve count]
[receiver count]
for each source:
     [source performance] list of: [adjacent valve/receiver index] [edge capacity]
for each valve:
     [valve capacity] list of: [adjacent valve/receiver index] [edge capacity]
```
### Prezentacja wyników
- Lista punktów odbioru wraz z ilością wody, która do niego dopłynęła. Na przykład:  
 ```
  1: 0.434414  
  2: 0.0855754  
  3: 0.474005  
  4: 0.0593254  
  5: 0.0742435  
SUM: 1.12756  
```
- Badanie złożoności
```
Ilość zaworów;ilość odcinków;czas rozwiązywania
100;268;152090
110;303;203680
120;350;271294
```
- Wykres czasu od oczekiwanej złożoności (więcej w dokumentacji)

## Krótki opis metody rozwiązania, zastosowanych algorytmów i struktur danych

- Język: C++
- Zastosowane algorytmy:
    - algorytm Edmondsa-Karpa
        - znalezienie ścieżki powiększającej w grafie
        - aktualizacja przepływu w grafie wzdłuż tej ścieżki
        - jeśli nie istnieje już żadna ścieżka powiększająca w grafie => zakończ. W p.p. wróć do p.1
    - znalezienie ścieżki powiększającej w grafie: algorytm BFS
- Wartość zwracana: lista punktów odbioru wraz z ilością wody, która do niego dopłynęła.
- Złożoność: O( E\*E\*V + E\*V\*V )
- Struktury danych:
    - Graph: wektor obiektów Vertice
    - Vertice: tablica mieszająca o kluczu numer wierzchołka sąsiada i wartości obiekt Edge
    - Edge: atrybuty danej krawędzi
## Informacje o funkcjonalnej dekompozycji programu na moduły źródłowe - nagłówkowe i implementacyjne ("przewodnik" po plikach źródłowych)

## Inne informacje dodatkowe o szczególnych decyzjach projektowych
- Ograniczenia dotyczące rozmiaru problemu: na CPU RAM 8GB dla 10000 wierzchołków generacja i rozwiązanie wymaga kilku minut.
- Charakterystyki generatorów danych testowych: generator tworzy obiekt klasy Graph 
- Konwencje we/wy:
    - przekierowanie z pliku
    - podanie nazwy pliku jako argument
- Alokacja pamięci dynamicznej: korzystanie z inteligentnych wskaźników C++
- Konwencje związane z obsługą sytuacji wyjątkowych:
    - wszystkie linie funkcji main są otoczone blokiem try. Wewnątrz metody rzucają wyjątkami.
    - najbardziej prawdopodobne sytuacje wyjątkowe to nieistniejący plik wejściowy.
    - program zakłada, że wprowadzone dane są prawdziwe 
- 