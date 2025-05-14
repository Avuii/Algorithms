#include <iostream>
#include <vector>
using namespace std;

long long Calculate(vector <int> *seq1, vector <int> *seq2)
{
    long long result = 0; // ostateczna suma
    long long sum1 = 0, sum2 = 0; // seq1, seq2


    //indeksy sekwencji
    unsigned int s1 = 0, s2 = 0;

    if (seq1->size() < seq2->size()) // Upewniamy się, że seq1 jest zawsze większy lub równy seq2
    {
        vector<int>* temp = seq1;
        seq1 = seq2;
        seq2 = temp;
    }

    while (s1 < seq1->size())
    {
        while (s2 + 1 < seq2->size() && (*seq2)[s2 + 1] <= (*seq1)[s1])
        {
            sum2 += (*seq2)[s2];
            s2++;
        }

        // Jeśli znaleźliśmy wspólny element w obu wektorach
        if ((*seq1)[s1] == (*seq2)[s2])
        {
            // Dodajemy większą sumę do sumy wynikowej
            if (sum2 > sum1)
            {
                result += sum2;
            }
            else
            {
                result += sum1;
            }

            sum1 = sum2 = 0; // reset dla kolejnych
        }

        sum1 += (*seq1)[s1];
        s1++;
    }

    result += sum1;

    return result;
}

int main()
{

    while (true)
    {
        unsigned int size1, size2; // rozmiary sekwencji
        vector <int> seq1, seq2;

        cin >> size1;

        // warunek koncowy
        if (size1 == 0)
            break;

        for (int i = 0; i < size1; i++)
        {
            int numberS1;
            cin >> numberS1;
            seq1.push_back(numberS1); //dzieki push_back() dodajemy dynamicznie elementy do wektora
        }

        cin >> size2;

        for (int i = 0; i < size2; i++)
        {
            int numberS2;
            cin >> numberS2;
            seq2.push_back(numberS2);
        }

        cout << Calculate(&seq1, &seq2) << "\n";
    }
}

