
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

/***********************************************************************************************************************
*** Complex
***********************************************************************************************************************/

template<typename T> struct Complex final
{
	Complex() : x(T()), y(T())
	{
	}

	template <typename U> Complex(Complex<U> const& r) : x(T(r.x)), y(T(r.y))
	{
	}

	Complex(T const& x, T const& y) : x(x), y(y)
	{
	}

	template <typename U> Complex& operator=(Complex<U> const& r)
	{
		x = T(r.x);
		y = T(r.y);

		return *this;
	}

	T x, y;
};

//**********************************************************************************************************************

template <typename T> Complex<T> operator+(Complex<T> const& r)
{
	return { +r.x, +r.y };
}

template <typename T> Complex<T> operator-(Complex<T> const& r)
{
	return { -r.x, -r.y };
}

template <typename T> T abs(Complex<T> const& r)
{
	return sqrt(r.x * r.x + r.y * r.y);
}

template <typename T> Complex<T> exp(Complex<T> const& r)
{
	return { exp(x) * cos(y), exp(x) * sin(y) };
}

template <typename T> Complex<T> sin(Complex<T> const& r)
{
	return { sin(x) * cosh(y), cos(x) * sinh(y) };
}

template <typename T> Complex<T> cos(Complex<T> const& r)
{
	return { cos(x) * cosh(y), sin(x) * sinh(y) };
}

template <typename T> Complex<T> sinh(Complex<T> const& r)
{
	return { sinh(x) * cos(y), cosh(x) * sin(y) };
}

template <typename T> Complex<T> cosh(Complex<T> const& r)
{
	return { cosh(x) * cos(y), sinh(x) * sin(y) };
}

//**********************************************************************************************************************
