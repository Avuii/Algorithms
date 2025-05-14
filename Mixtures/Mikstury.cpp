/*SORTOWANIE TOPOLOGICZNE
Zamierzasz rozpocząć własny biznes. Będzie on polegał na importowaniu i sprzedawaniu
w Twoim miescie magicznych mikstur od wielkiego Maga z dalekiego kraju. Cena danej mikstury
jest ustalona i jednakowa u Maga i u Ciebie. Twoją umiejętnością jest bezkosztowna transmutacja
między niektórymi rodzajami mikstur. Zadanie polega na pokazaniu jaki jest największy zysk,
który można osiągnąc na zakupie jednej z mikstur. Każda transmutacja jest jednokierunkowa.

-? Jak zbudować graf z danych ( przekazanych przez plik wejsciowy)

WEJŚCIE
T-liczba przypadków testowych ( 1 =< T =< 100)
N M - dwie liczby całkowite znajdujące sie w kazdym wierszu
( N to liczba mikstur sprzedawanych przez maga, M to liczba transmutacji)
(1 =< N =< 100) (1 =< M =< N*(N-1) / 2)
A, A2, ... Ai  - kolejny wiersz zawiera N liczb całkowitych z zakresu od 1 do 10^5. Są to ceny mikstur.
Kolejne M wierszy zawiera opis kolejnych transmutacji opisanych przrz podanie nr początkowej i finalnej mikstury.
Każda para liczb może pojawić się w zestawie najwyżej jeden raz. Numeracja zaczyna się od 1 i odpowiada wcześniej
podanej kolejności mikstur.

WYJŚCIE
Każdy wiersz odpowiada jednemu przypadkowi testowemu w kolejnosci takiej jakiej znajduja sie w pliku wejsciowym.
Jest to maksymalny zysk uzyskany w efekcie łańcucha transmutacji.
*/

//SORTOWANIE KHAN ALGORITHM
//Znajduje wierzchołki, które nie mają poprzedników (degree[i] == 0).
//Dodaje je do kolejki (q).
//Przetwarza kolejne wierzchołki, zmniejsza stopnie wejściowe ich sąsiadów.
//Uzyskujemy kolejność topologiczną w order[].


#include <iostream>
#include <vector>
#include <queue>
#include <climits> // INT_MAX

using namespace std;

const int MAX_N = 100;  // Maksymalna liczba mikstur
const int MAX_M = MAX_N * (MAX_N - 1) / 2; // Maksymalna liczba transmutacji

vector<int> prices;         // Ceny mikstur
vector<int> minPrice;       // Minimalna cena na ścieżce
vector<vector<int>> graph;  // Lista sąsiedztwa
vector<int> degree;         // Stopnie wejściowe
vector<int> order;          // Kolejność topologiczna

void InitializeGraph(int N)
{
    prices.assign(N, 0);
    minPrice.assign(N, INT_MAX);
    graph.assign(N, vector<int>());
    degree.assign(N, 0);
    order.assign(N, 0);
}

void ReadPrices(int N)
{
    for (int i = 0; i < N; i++)
    {
        cin >> prices[i];
    }
}

bool ReadEdges(int M, int N)
{
    for (int i = 0; i < M; i++)
    {
        int u, v;
        cin >> u >> v;
        if (u < 1 || v < 1 || u > N || v > N)
        {
            cerr << "Błąd: Niepoprawne indeksy krawędzi." << endl;
            return false;
        }
        u--; v--; // Indeksy od 0
        graph[u].push_back(v);
        degree[v]++;
    }
    return true;
}

bool KhanAlgorithm(int N)
{
    queue<int> q;
    int index = 0;

    for (int i = 0; i < N; i++)
    {
        if (degree[i] == 0)
        {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order[index++] = u;

        for (int v : graph[u])
        {
            degree[v]--;
            if (degree[v] == 0)
            {
                q.push(v);
            }
        }
    }
    return index == N;
}

int MaxProfit(int N)
{
    int maxProfit = 0;
    for (int i = 0; i < N; i++)
    {
        int v = order[i];
        if (minPrice[v] == INT_MAX) minPrice[v] = prices[v];

        for (int next : graph[v])
        {
            minPrice[next] = min(minPrice[next], minPrice[v]);
            maxProfit = max(maxProfit, prices[next] - minPrice[next]);
        }
    }
    return maxProfit;
}

int main() {
    int T;
    cin >> T;

    if (T < 1 || T > 100)
    {
        cerr << "Błąd: Liczba testów poza zakresem." << endl;
        return 1;
    }

    while (T--)
    {
        int N, M;
        cin >> N >> M;

        if (N < 1 || N > MAX_N || M < 0 || M > MAX_M)
        {
            cerr << "Błąd: Niepoprawne wartości N lub M." << endl;
            return 1;
        }

        InitializeGraph(N);
        ReadPrices(N);

        if (!ReadEdges(M, N)) return 1;

        if (!KhanAlgorithm(N))
        {
            cerr << "Błąd: Cykl w grafie, brak sortowania topologicznego." << endl;
            return 1;
        }

        cout << MaxProfit(N) << endl;
    }

    return 0;
}