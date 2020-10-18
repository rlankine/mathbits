
#include "Statistics.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

int testStatistics()
{
    cout << std::setprecision(5);

    RegressionAccumulator<double> acc;

    // Example comes from https://en.wikipedia.org/wiki/Simple_linear_regression

#if 1
    acc.insert(1.47, 52.21);
    acc.insert(1.50, 53.12);
    acc.insert(1.52, 54.48);
    acc.insert(1.55, 55.84);
    acc.insert(1.57, 57.20);
    acc.insert(1.60, 58.57);
    acc.insert(1.63, 59.93);
    acc.insert(1.65, 61.29);
    acc.insert(1.68, 63.11);
    acc.insert(1.70, 64.47);
    acc.insert(1.73, 66.28);
    acc.insert(1.75, 68.10);
    acc.insert(1.78, 69.92);
    acc.insert(1.80, 72.19);
    acc.insert(1.83, 74.46);
#else
    acc.insert(2, 2);
    acc.insert(5, 7);
    acc.insert(3, 5);
#endif

    cout << acc.gain() << endl;
    cout << acc.bias() << endl;
    cout << acc.correlation() << endl;

    cout << "-----------" << endl;

    for (int i = 0; i < 10; ++i)
    {
        cout << i << "\t" << acc(i) << "\t" << acc.inv(i) << endl;
    }

    return EXIT_SUCCESS;
}
