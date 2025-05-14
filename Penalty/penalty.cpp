//PENALTY
// FIFA rozważa kilka zmian w sposobie organizacji Mistrzostw Świata w Piłce Nożnej.
// Obecnie 32 drużyny rywalizują o tytuł mistrza świata w dwóch etapach.
// W pierwszym etapie, zwanym fazą grupową, 32 drużyny są równomiernie podzielone na 8 grup.
// Każda drużyna w grupie rozgrywa 3 mecze – po jednym z każdą drużyną z własnej grupy.
// Następnie drużyny są klasyfikowane według ustalonego systemu punktowego.
// W drugim (i ostatnim) etapie dwie najlepsze drużyny z każdej grupy awansują do fazy pucharowej,
// gdzie rozegranych zostaje osiem meczów, z których wyłaniane są ośmiu zwycięzców.
// Zwycięzcy ci rozgrywają kolejno cztery mecze, aby wyłonić cztery drużyny, potem dwa mecze,
// które wyłaniają dwie drużyny, a następnie odbywa się mecz finałowy decydujący o mistrzu świata.
// Nie trzeba dodawać, że dla prawidłowego funkcjonowania fazy pucharowej
// liczba drużyn musi być potęgą dwójki. FIFA rozważa dodanie większej liczby grup,
// zwiększenie liczby drużyn w grupach oraz ewentualną zmianę liczby drużyn awansujących z każdej grupy
// do fazy pucharowej. Ponadto, FIFA rozważa, aby niektóre drużyny (np. poprzedni mistrz, kraj gospodarza itd.)
// awansowały bezpośrednio do fazy pucharowej, bez konieczności udziału w fazie grupowej.
// Jednak FIFA musi wiedzieć, ile meczów zostanie rozegranych, jeśli zostaną wprowadzone którekolwiek z tych zmian.

#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream infile("wakawaka.in");
    ofstream outfile("wakawaka.out");

    if (!infile || !outfile)
    {
        cout << "Błąd otwarcia plików!" << endl;
        return 1;
    }

    while (true)
    {
        long long G, T, A, D;
        infile >> G >> T >> A >> D;

        // Sprawdzamy warunek END: -1 -1 -1 -1
        if (G == -1 && T == -1 && A == -1 && D == -1)
            break;


        // Każda grupa z T drużynami rozgrywa T*(T-1)/2 meczów.
        long long groupGames = G * (T * (T - 1) / 2);

        // drużyn, które awansują z grup
        long long teamsFromGroups = G * A;

        // drużyny do fazy pucharowej
        long long knockoutTeams = teamsFromGroups + D;

        // Trzeba znalezc najmneijsza potęgę dwójki ale nie mniejszą od knockoutTeams
        long long P = 1;
        while (P < knockoutTeams)
        {
            P *= 2;
        }

        // ile jest uzupełniających drużyn
        long long extra = P - knockoutTeams;

        // mecze fazy pucharowej
        long long knockoutGames = P - 1;

        long long totalGames = groupGames + knockoutGames;

        outfile << G << "*" << A << "/" << T << "+" << D << "=" << totalGames << "+" << extra << endl;
    }

    infile.close();
    outfile.close();
    return 0;
}

