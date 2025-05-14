// SORTOWANIE STOGOWE
//zakres liczb które będzie sortować program [-10^9  , 10^9]
// Wejście
// W pierwszej linii pliku wejściowego znajduje się liczba całkowita określająca liczbę przypadków
// testowych N . Następnie znajduje się opis kolejnych przypadków testowych, przy czym opis
// każdego przypadku zawiera się w jednej linii. Pierwsza liczba w linii (k ) odpowiada liczbie
// elementów w zbiorze, następnie znajduje się k liczb w kolejności odpowiadającej aktualnej
// kolejności elementów w zbiorze.
// Wyjście
//Wyjście zawiera kolejno N bloków opisujących przebieg sortowania rozdzielonych pustymiliniami.
//Każdy blok musi zawierać dokładnie k linii, zawierających kolejno:
//zawartość kopca zupełnego tworzonego w czasie sortowania po każdym kolejnym kopcowaniu,
//bez kopca zawierającego tylko korzeń i bez dalszej części tablicy oraz ostatecznie posortowany zbiór.

#include <iostream>

using namespace std;

// Kopcowanie
void heapify(int arr[], int n, int i, ostream &out)
{
    int largest = i;  // Korzeń
    int left = 2 * i + 1;  // Indeks lewego dziecka
    int right = 2 * i + 2; // Indeks prawego dziecka

    if (left < n && arr[left] > arr[largest]) // Jeśli lewe dziecko jest większe od rodzica
        largest = left;

    if (right < n && arr[right] > arr[largest]) // Jeśli prawe dziecko jest większe od obecnie największego
        largest = right;

    if (largest != i) // Jeśli znaleziono większe dziecko, zamieniamy miejscami i rekurencyjnie kopcujemy
    {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, out);
    }
}

void heapSort(int arr[], int n, ostream &out)
{
    // Tworzenie kopca
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i, out);
    }

    // Wypisywanie początkowego kopca
    for (int j = 0; j < n; j++)
    {
        out << arr[j] << " ";
    }
    out << endl;

    // Usuwanie elementów z kopca i sortowanie
    for (int i = n - 1; i > 0; i--)
    {
        swap(arr[0], arr[i]); // Przeniesienie największego elementu na koniec
        heapify(arr, i, 0, out); // Kopcujemy zmniejszony kopiec

        // Wypisywanie tylko tej części, która nadal jest kopcem
        for (int j = 0; j < i; j++)
        {
            out << arr[j] << " ";
        }
        out << endl;
    }
}

int main()
{
    int N;
    cin >> N; // Liczba przypadków testowych

    for (int test = 0; test < N; test++)
    {
        int k; // Liczba elementów w zbiorze
        cin >> k;
        int* tab = new int[k];

        // Wczytywanie wartości
        for (int i = 0; i < k; i++)
        {
            cin >> tab[i];
        }

        heapSort(tab, k, cout);

        // Wypisanie posortowanego zbioru
        for (int i = 0; i < k; i++)
        {
            cout << tab[i] << " ";
        }
        cout << endl << endl;

        delete[] tab;
    }

    return 0;
}
