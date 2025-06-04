///DJIKSTRA
///
///Podstawowym dochodem Ardenii jest zarobek ze sprzedaży złota w sąsiedniej Bitlandii. Niestety
///jako, że kreól Bitlandii też chce zarobić na przywozie złota i nie tylko złota, nałożył na każdy
///przywożony do swojego kraju metal podstek wynosi 50% jego ceny. Szczęśliwie dla władcy i kupców
///ardeńskich, alchemicy opracowali spodoby pozwalające zamieniać pewne metale w inne. Pomysł polega
///na tym, aby za pomocą alchemików zamieniać złoto w pewien tani metal, a następnie po przewiezieniu
///go przez granicę i zapłaceniu niewielkiego cła, znowu otrzymywać z niego złoto. Niestety alchemicy
///nie znaleźli sposobu na zamianę dowolnego metalu na dowolny inny. Może się więc zdarzyć, że proces
///otrzymania danego metalu ze złota musi przebiegać wielostopniowo i że na każdym etapie uzyskiwany
///będzie inny metal. Alcgemicy każą sobie słono płacić za swoje usługidego znanego sobie procesu
///zamiany metalu A w metal B wyznaczyli sobie cene za przemiane 1kg surowca. Kupcy zastanawiaja sie,
///w jakiej postaci nalezy przewozic zloto przez granice oraz jaki ciag procesow alchemicznych nalezy
///zastosowac, aby zyski byly mozliwie najwieksze. Celem zadania jest wsparcie kupców w ich dziele.
///
///WEJSCIE
///W pierwszym wierszu znajduje sie liczba przypadkow testowych T (1=<T<=100). Opis każdego przypadku testowego wygląda
///nastepująco
///Pierwszy wiersz zawiera liczbe rodzajów metali n (1=<n=<5000). Każdy z kolejnych n wierszy zawiera parzystą liczbę
///całkowitą p(k) (1=<p(k)=<10^9)- cenę 1kg kolejnych metali, przy czym k=1 oznacza złoto, a metale numerowane sa przez
///kolejny nr wiersza. W kolejnym wierszu znajduje się jedna nieujemna liczba calkowita m równa liczbie procesów
///przemiany znanych alchemikom (1=<m=<10^5). Kolejne m wierszy zawiera trójki liczb a,b,c opisujące możliwe przemiany.
///Taka trójka liczb oznacza, że alchemicy potrafią z metalu o numerze a otrzymać metak o numerze b i za zamiane 1kg
///kaza sobie zaplacic kwote c (1=<a,b=<n , 1=<c=<10000).
///WAŻNE: Uporządkowana para liczb a i b może pojawić się w danych co najwyżej raz !!!
///
///WYJCIE:
///Każdy wiersz wyjścia powinien odpowiadać jednemu przypadkowi testowemu, w kolejnośći takiej, w jakiej znajdują się
///one w pliku wejściowym. Dla każdego przypadku testowego należy wprowadzić pojedyńczą liczbę całkowitą oznaczającą
///koszt wykonania wyznaczonego ciągu procesów alchemicznych powiekszony o płacone na granicy cło!!!
///
///Co jest potrzebne do rozwiązania problemu? Single-Source Shortest Paths (SSSP)
///Bellman-Ford , BFS , DFS , Dijkstra
///Wybieramy -DJIKSTRA

//alchemia.in
//1            // liczba testów T
//4            // liczba metali n
//200          // p[1] = złoto = 200
//100          // p[2]
//40           // p[3]
//2            // p[4]
//6            // liczba możliwych przemian m
//1 2 10       // złoto -> metal 2, koszt 10
//1 3 5        // złoto -> metal 3, koszt 5
//2 1 25       // metal 2 -> złoto, koszt 25
//3 2 10       // metal 3 -> metal 2, koszt 10
//3 4 5        // metal 3 -> metal 4, koszt 5
//4 1 50       // metal 4 -> złoto, koszt 50

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Funkcja Dijkstry – znajduje najtańszy koszt przejścia z metalu startowego do innych
vector<long long> dijkstra(int start, const vector<vector<pair<int, int>>>& graph, int n)
{
    vector<long long> zamiana(n + 1, numeric_limits<long long>::max());
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;

    zamiana[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        long long koszt = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (koszt > zamiana[u]) continue;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int cena = edge.second;
            if (zamiana[v] > koszt + cena)
            {
                zamiana[v] = koszt + cena;
                pq.push({zamiana[v], v});
            }
        }
    }
    return zamiana;
}

int main() {
    int T; //liczba testow
    cin >> T;

    while (T--) {
        int n;//liczba metali
        cin >> n;

        vector<long long> cena_metalu(n + 1);  // cena 1 kg każdego metalu
        for (int i = 1; i <= n; ++i) {
            cin >> cena_metalu[i];
        }

        int m; //liczba przemian
        cin >> m;

        // graf przemian (z a do b za c) - wierzchołkami grafu są metale.
        vector<vector<pair<int, int>>> graf(n + 1);

        // odwrotny graf (potrzebny do wyznaczenia ścieżki powrotnej)
        vector<vector<pair<int, int>>> graf_odwrotny(n + 1);

        for (int i = 0; i < m; ++i)
        {
            int a, b, c;
            cin >> a >> b >> c;
            graf[a].push_back({b, c});
            graf_odwrotny[b].push_back({a, c});
        }

        // Obliczamy koszt zamiany złota (metal 1) na każdy inny metal
        vector<long long> koszt_do = dijkstra(1, graf, n);

        // Obliczamy koszt powrotnej zamiany do złota
        vector<long long> koszt_z = dijkstra(1, graf_odwrotny, n);

        long long wynik = numeric_limits<long long>::max();

        for (int i = 1; i <= n; ++i)
        {
            // Sprawdzamy tylko metale, do których można dojść i wrócić
            if (koszt_do[i] != numeric_limits<long long>::max() &&
                koszt_z[i] != numeric_limits<long long>::max())
                {

                // Całkowity koszt: zamiana w tę i z powrotem + cło (50%)
                long long calkowity_koszt = koszt_do[i] + koszt_z[i] + cena_metalu[i] / 2;
                wynik = min(wynik, calkowity_koszt);
            }
        }

        // Jeśli nie udało się znaleźć żadnej ścieżki
        if (wynik == numeric_limits<long long>::max())
            {
            cout << -1 << '\n';
        } else {
            cout << wynik << '\n';
        }
    }

    return 0;
}

