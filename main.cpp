
#include "Complex.h"
#include "Geometry3D.h"
#include "MathBits.h"
#include "Polylog2.h"
#include "Statistics.h"
#include "Summation.h"

#include <iostream>
#include <iomanip>

using std::cout;
using std::endl;

using Summation = SummationOf<double>;

int main(int argc, char const* argv[]) try
{
    StatisticsAccumulator<double> stat;
    Summation sum;
    double add = 0;

    for (int i = 0; i < 100000000; ++i)
    {
        double d = pow(i + 1, -1);
        add += d;
        stat.insert(d);
        sum += (d/1.0e8);
    }

    cout << std::setprecision(19);
    cout << add / 1.0e8 << endl;
    cout << stat.average() << endl;
    cout << sum << endl;
    cout << 18.997896413853898324417110394223982841850971244970103438818422187516843136486601250840227517775930459077L / 1.0e08L << endl;

    // Complex<double> a;

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
