
/*
MIT License

Copyright(c) 2022 Risto Lankinen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
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

#include <cmath>

/***********************************************************************************************************************
*** Template functions
***********************************************************************************************************************/

template <typename T> T CostW(T const& x)  // Bimodal cost function (bottoms at x = 1 and at x = -1 )
{
	return (x * x - 1) * (x * x - 1) / (x * x + 1);
}

template <typename T> T InvAct(T const& x)  // Reversible activation function ( InvAct(InvAct(x)) = x )
{
	return sqrt(x * x + 1) - sqrt(2) * x;
}

template <typename T> T Logistic(T const& x)
{
	return 1 / (1 + exp(-x));
}

template <typename T> T Maximum(T const& x, T const& y)
{
	return (x + y + abs(x - y)) / 2;
}

template <typename T> T Minimum(T const& x, T const& y)
{
	return (x + y - abs(x - y)) / 2;
}

template <typename T> T ReLU(T const& x)
{
	return Maximum(x, 0);
}

template <typename T> T Restrict(T const& x, T const& a, T const& b)
{
	return (abs(x - Minimum(a, b)) - abs(x - Maximum(a, b)) + a + b) / 2;
}

template <typename T> T SoftPlus(T const& x)
{
	return log(1 + exp(x));
}

//**********************************************************************************************************************
