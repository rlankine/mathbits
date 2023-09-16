
/*
MIT License

Copyright (c) 2023 Risto Lankinen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
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
	Complex() : re(T()), im(T())
	{
	}

	template <typename U> Complex(Complex<U> const& r) : re(T(r.re)), im(T(r.im))
	{
	}

	Complex(T const& re, T const& im) : re(re), im(im)
	{
	}

	template <typename U> Complex& operator=(Complex<U> const& r)
	{
		re = T(r.re);
		im = T(r.im);

		return *this;
	}

	T re;
	T im;
};

//**********************************************************************************************************************

template <typename T> Complex<T> operator+(Complex<T> const& r)
{
	return { +r.re, +r.im };
}

template <typename T> Complex<T> operator-(Complex<T> const& r)
{
	return { -r.re, -r.im };
}

template <typename T> Complex<T> operator+(Complex<T> const &r, Complex<T> const &s)
{
	return { r.re + s.re, r.im + s.im };
}

template <typename T> Complex<T> operator-(Complex<T> const &r, Complex<T> const &s)
{
	return { r.re - s.re, r.im - s.im };
}

template <typename T> Complex<T> operator*(Complex<T> const &r, Complex<T> const &s)
{
	return { r.re * s.re - r.im * s.im, r.re * s.im + r.im * s.re };
}

template <typename T> T abs(Complex<T> const& r)
{
	return sqrt(r.re * r.re + r.im * r.im);
}

template <typename T> Complex<T> exp(Complex<T> const& r)
{
	return { exp(r.re) * cos(r.im), exp(r.re) * sin(r.im) };
}

template <typename T> Complex<T> sin(Complex<T> const& r)
{
	return { sin(r.re) * cosh(r.im), cos(r.re) * sinh(r.im) };
}

template <typename T> Complex<T> cos(Complex<T> const& r)
{
	return { cos(r.re) * cosh(r.im), sin(r.re) * sinh(r.im) };
}

template <typename T> Complex<T> sinh(Complex<T> const& r)
{
	return { sinh(r.re) * cos(r.im), cosh(r.re) * sin(r.im) };
}

template <typename T> Complex<T> cosh(Complex<T> const& r)
{
	return { cosh(r.re) * cos(r.im), sinh(r.re) * sin(r.im) };
}

//**********************************************************************************************************************
