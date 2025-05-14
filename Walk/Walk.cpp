
#include <iostream>
#include <cmath> //ceil()
using namespace std;

int main()
{
    int stepCases;
    double step, result;
    cin >> stepCases;
    for (int i=0; i < stepCases; i++)
    {
        cin >> step;

        if (step < 1 || step > 3000)
        {
            cout << "error" <<endl;
            return -1;
        }

        result = ceil(3000.0 / step);
        if (result > 15)
            result = 15;
        cout << result<<endl;

    }
    return 0;
}

