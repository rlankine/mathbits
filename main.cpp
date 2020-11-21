
#include "Geometry3D.h"
#include "MathBits.h"
#include "Polylog2.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

int main()
{
    cout << std::setprecision(15);

    for (int i = 0; i < 45; ++i)
    {
        double d = 1 - i/5.0;
        cout << d << "\t";
        cout << Li2(d) << "\t";
        cout << endl;
    }

    return EXIT_SUCCESS;
}

int main0(int argc, char const* argv[]) try
{
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
