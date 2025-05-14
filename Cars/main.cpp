/// Samochody elektryczne maja problem z optymalizacja zasiegu. Z jednej strony zwiekszenie zasiegu wymaga
/// zwiekszenia wielkosci baterii, z drugiej strony z wielkoscia baterii rosnie masa samochodu.
/// Wyobrazmy sobie kraj w ktorym drogi dwukierunkowe łączą pewne pary miast. Znając długość tych dróg
/// oraz wiedzac ze stacje ladowania znajduja sie w kazdym miescie i tylko w miescie, trzeba okreslic minimalny
/// zasieg samochodu elektrycznego wymagany, aby moc dotrzec do dowolnego miasta w kraju.
///
/// wejscie
/// pierwszy wiersz T ( 1=< T =< 100) liczba przypadkow testowych
/// opis kazdego przypadku testowegowyglada nastepujaco:
/// pierwszy wiersz przypadku testowego zawiera n i m (1=< n =<1000, 1=< m =<10000 )
/// n- liczba miast, m - ilosc drog
/// miasta sa numerowane od 0 do n-1, kolejne m wierszy zawiera po 3 liczby calkowite rozdzielone spacjami.
/// pierwsze 2 liczby oznaczaja numery miast trzecia to odleglosc miedzy nimi
///  numery sa w przedziale [0,n-1], odleglosc dodarnia i mniejsza od 1000000
///  pomiedzy para miast istnieje conajwyzej jedna droga.
///
///  wyjscie
///  kazdy wiersz odpowiada jednemu przypadkowi testowemu w kolejnosci takiej jakiej znajduja sie w pliku wejsciowym.
///  wynik to minimalny zasieg samochodu, ktory umozliwi mu dojechanie do dowolnego miasta z wykorzystaniem podanej
///  seci drog.

//Musimy znaleźć maksymalną długość drogi w minimalnym drzewie rozpinającym (MST)

//DSU – struktura zbiorów rozłącznych (ang. Union-Find). Służy do budowy MST przez Kruskala,
//zapewniając, że nie tworzymy cykli.

/*
Kruskal — Budowa MST
Iterujemy po posortowanych krawędziach i:
    * Jeżeli dwa miasta u i v nie są jeszcze połączone(czyli należądo różnych zbiorów), łączymy je (dsu.unite)
    * Każda taka krawędź wchodzi do MST
    * Jednocześnie zapamiętujemy najdłuższą krawędź w MST: maxEdgeInMST
Jeśli mamy już n-1 krawędzi w MST — to wystarczy(bo MST w grafie o n wierzchołkach ma zawsze n- 1 krawędzi)

Drzewo rozpinające (MST)?
To takie poddrzewo grafu, które:
    * Zawiera wszystkie wierzchołki (miasta),
    * Nie zawiera cykli,
    * Ma minimalną możliwą sumę wag krawędzi,
    * Zawiera dokładnie n−1 krawędzi (dla n wierzchołków).
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//Droga
struct Edge
{
    int u, v, w; //miasta u,v i dl. drogi - w
    bool operator<(const Edge& other) const
    {
        return w < other.w; //sort po dl drogi - w - przygotowanie do kruskala
    }
};

//struktura zbiorow rozlacznych Union-find/dsu do wykrywania cykli i laczenia komponentow

struct DSU  //graf nieskierowany, ważony i spójny
{
    vector<int> parent, rank;

    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        //kazdy wierzcholek jest na poczatku swoim wlasnym rodzicem
        for(int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    //laczymy dwa zbiory
    bool unite(int x, int y)
    {
        int xr = find(x), yr = find(y);
        if (xr == yr) return false; //juz polaczone
        if (rank[xr] < rank[yr])
            parent[xr] = yr;
        else {
            parent[yr] = xr;
            if (rank[xr] == rank[yr])
                rank[xr]++;
        }
        return true;
    }
};

int main() {
    int T;
    cin >> T; // ile testow
    while (T--) {
        int n, m;
        cin >> n >> m; // ile miast i drog
        vector<Edge> edges(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v >> edges[i].w;
        }

        sort(edges.begin(), edges.end()); //sort rosnaco drog wedlug dlugosci

        DSU dsu(n); // zbiory rozłaczne sa tworzone

        int maxEdgeInMST = 0, edgesUsed = 0; //najwieksza dl drogi, ile krawedzi dodano

        // Algorytm Kruskala - dodajemy najkrótsze drogi które nie tworzą cykli
        for (const auto& edge : edges) {
            if (dsu.unite(edge.u, edge.v)) {
                maxEdgeInMST = max(maxEdgeInMST, edge.w); //trzymamy maks dł drogi w mst
                edgesUsed++;
                if (edgesUsed == n - 1) //kiedy mamy już MST (n-1 krawędzi)
                    break;
            }
        }

        cout << maxEdgeInMST << endl;
    }
    return 0;
}


