// Mamy dwa klasyczne zegary, które podają czas w formacie: hour:minutes:second.hundredths, i mają zakres 0:0:0.00   11:59:59.99.
// Zegar1 ma być przesuniety o 1 sekunde. Każdy z nich pokazuje jakiś czas. Zegar1: 4:10:20.55  Zegar2: 8:30:5.10. Znamy kąt pomiedzy wskazówkami zegara.
// Chcemy policzyć pole wycinka tarczy zegara pomiędzy małymi wskazówkami ( nakładamy tarcze dwóch zegarów na siebie i patrzymy tylko na wskazówki godzinowe -te małe)
// Kąt ruchu małej wskazówki w radianach = (różnica czasu w sekundach) * (30 stopni na godzinę / 3600 sekund)
// Przesunięcie małej wskazówki (30 stopni na godzinę, 3600 sekund w godzinie)
//pierwsza linijka w pliku wsadowym clock.in to ilość testow D, każdy test m a 3 linijki:
//  w 1 linijce jest czas na zegar1, w drugiej linijce czas zegar2, a w trzeciej kąt w radianach pomiędzy wskazówkami.
// Czas będziemy przechwytywać za pomocą zmiennych H (hours) M (minutes) S (secund) U (hudnreaths).
// WAŻNE: 0=< H <12,0 =< M<60,0 =< S < 60      i    0 =< U < 100
// trzeba zabezpieczyć się przed niepożadanymi wartościami !!!
//Przykład clock.in
//2
// 4 10 20 55
// 8 30 5 10
//20.5
//3 58 58 44
// 10 10 7 22
// 22.5
//Przykład clock.out
// 1. 476.286
// 2. 801.720
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

const double PI = 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214;

int main() {
    ifstream infile("clock.in");
    ofstream outfile("clock.out");

    if (!infile || !outfile) {
        cerr << "Błąd otwarcia plików!" << endl;
        return 1;
    }

    int D; // Liczba testów
    infile >> D;

    for (int i = 1; i <= D; i++) {
        int H1, M1, S1, U1;
        int H2, M2, S2, U2;
        double clockSize;

        infile >> H1 >> M1 >> S1 >> U1;
        infile >> H2 >> M2 >> S2 >> U2;
        infile >> clockSize;

        // Konwersja  na setne sekundy
        int maxTimeInMS = 12 * 60 * 60 * 100; // Maks 12 h
        int timeInMs1 = (((H1 * 60) + M1) * 60 + S1) * 100 + U1;
        int timeInMs2 = (((H2 * 60) + M2) * 60 + S2) * 100 + U2;

        // Różnica czasu jako ułamek pełnego obrotu tarczy
        double fraction = (timeInMs2 * 1.0 / maxTimeInMS) - (timeInMs1 * 1.0 / maxTimeInMS);


        //Pole wycinka = (różnica ułamkowa) * PI * (clockSize)^2
        double Area = fraction * PI * clockSize * clockSize;

        // Formatowanie i zapis wyniku
        outfile << i << ". " << fixed << setprecision(3) << Area << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}
