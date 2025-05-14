//LIS - Longest Increasing Subsequence

#include <iostream>
#include <vector>

using namespace std;

int LonIncSub(vector<int>& seq)
{
    vector<int> lis;
    for (int num : seq)
    {
        int left = 0, right = lis.size();
        while (left < right)
        {
            int mid = left + (right - left) / 2;
            if (lis[mid] < num)
            {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        if (left < lis.size())
        {
            lis[left] = num;
        } else {
            lis.push_back(num);
        }
    }
    return lis.size();
}

int main() {


    int testCases;
    if (!(cin >> testCases) || testCases <= 0)
    {
        cerr << "Error: Invalid number of test cases" << endl;
        return 1;
    }

    while (testCases--)
    {
        int p;
        if (!(cin >> p) || p <= 0 || p >= 100000) {
            cerr << "Error: Invalid number of ports" << endl;
            continue;
        }

        vector<int> sequence(p);
        bool validInput = true;
        for (int i = 0; i < p; i++)
        {
            if (!(cin >> sequence[i]) || sequence[i] < 1 || sequence[i] > p)
            {
                cerr << "Error: Invalid port mapping" << endl;
                validInput = false;
                break;
            }
        }

        if (!validInput) continue;

        cout << LonIncSub(sequence) << endl;
    }

    return 0;
}

