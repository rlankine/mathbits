
#include "Complex.h"
#include "Geometry3D.h"
#include "MathBits.h"
#include "Polylog2.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

int main(int argc, char const* argv[]) try
{
    Complex<double> a;

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
