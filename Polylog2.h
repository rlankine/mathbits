
/*
MIT License

Copyright(c) 2020 Risto Lankinen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <assert.h>
#include <cmath>

//**********************************************************************************************************************

static inline double sq(double x) { return x * x; }
static double const PiPiDiv6 = 1.64493406684822644e-00;

//**********************************************************************************************************************

static inline double bernoulli(double x)
{
    assert(abs(x) <= log(2));

    double const x2 = x * x;
    double power[8];

    power[0] = x2 * x;
    power[1] = x2 * power[0];
    power[2] = x2 * power[1];
    power[3] = x2 * power[2];
    power[4] = x2 * power[3];
    power[5] = x2 * power[4];
    power[6] = x2 * power[5];
    power[7] = x2 * power[6];

    double total;

    total = -power[7] * 1.99392958607210757e-14;
    total += power[6] * 8.92169102045645256e-13;
    total -= power[5] * 4.06476164514422553e-11;
    total += power[4] * 1.89788699889709991e-09;
    total -= power[3] * 9.18577307466196355e-08;
    total += power[2] * 4.72411186696900983e-06;
    total -= power[1] * 2.77777777777777778e-04;
    total += power[0] * 2.77777777777777778e-02;

    return total + x - x2 / 4;
}

/***********************************************************************************************************************
*** Polylog2
***********************************************************************************************************************/

inline double Li2(double x)
{
    if (x < -1) return -Li2(1 / x) - PiPiDiv6 - sq(log(-x)) / 2;
    if (x <= 0.5) return bernoulli(-log1p(-x));
    if (x < 1) return -Li2(1 - x) + PiPiDiv6 - log(x) * log1p(-x);
    if (x == 1) return PiPiDiv6;
    return nan(__FUNCTION__);  // Reals only!
}

/***********************************************************************************************************************
*** Integral of SoftPlus
***********************************************************************************************************************/

inline double ISp(double x)
{
    if (x > 0) return x * x / 2 - ISp(-x) + PiPiDiv6;
    return -bernoulli(-log1p(exp(x)));
}

//**********************************************************************************************************************
