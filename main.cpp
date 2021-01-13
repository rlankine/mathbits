
#include "Geometry3D.h"
#include "MathBits.h"
#include "Polylog2.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

int main(int argc, char const* argv[]) try
{
    cout << std::setprecision(18);
    srand(time(nullptr));

    Quaternion<double> q = { double(rand()), double(rand()), double(rand()), double(rand()) };
    q = normalize(q);

    for (int i = 0; i < 5000; ++i)
    {
        cout << i << "\t" << pow(q, (i-2500.0) / 250.0) << endl;
    }

    return EXIT_SUCCESS;
}
catch (std::string const& r)
{
    cout << endl << r << endl;
    return EXIT_FAILURE;
}
catch (char const* p)
{
    cout << endl << p << endl;
    return EXIT_FAILURE;
}
catch (...)
{
    cout << endl << "Diva tantrum!!!!" << endl;
    return EXIT_FAILURE;
}
