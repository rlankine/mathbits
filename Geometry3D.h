
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

#include <iostream>
#include <type_traits>

// https://users.aalto.fi/~ssarkka/pub/quat.pdf

/***********************************************************************************************************************
*** Vector -- position or translation in 3D space
***********************************************************************************************************************/

template<typename T> struct Vector final
{
	Vector() : x(T()), y(T()), z(T())
	{
	}

	template <typename U> Vector(Vector<U> const& r) : x(T(r.x)), y(T(r.y)), z(T(r.z))
	{
	}

	Vector(T const& x, T const& y, T const& z) : x(x), y(y), z(z)
	{
	}

	template <typename U> Vector& operator=(Vector<U> const& r)
	{
		x = T(r.x);
		y = T(r.y);
		z = T(r.z);

		return *this;
	}

	T x, y, z;
};

//**********************************************************************************************************************

template <typename T> Vector<T> operator-(Vector<T> const& r)
{
	return Vector<T>(-r.x, -r.y, -r.z);
}

template <typename T> Vector<T> operator+(Vector<T> const& r, Vector<T> const& s)
{
	return Vector<T>(r.x + s.x, r.y + s.y, r.z + s.z);
}

template <typename T> Vector<T> operator-(Vector<T> const& r, Vector<T> const& s)
{
	return Vector<T>(r.x - s.x, r.y - s.y, r.z - s.z);
}

template <typename T> Vector<T> operator*(T const& r, Vector<T> const& s)
{
	return Vector<T>(r * s.x, r * s.y, r * s.z);
}

template <typename T> Vector<T> operator*(Vector<T> const& r, T const& s)
{
	return Vector<T>(r.x * s, r.y * s, r.z * s);
}

template <typename T> Vector<T> operator/(Vector<T> const& r, T const& s)
{
	return Vector<T>(r.x / s, r.y / s, r.z / s);
}

template <typename T> T abs(Vector<T> const& r)
{
	return sqrt(r.x * r.x + r.y * r.y + r.z * r.z);
}

template <typename T> Vector<T> normalize(Vector<T> const& r)
{
	return r / abs(r);
}

template <typename T> std::ostream& operator<<(std::ostream& out, Vector<T> const& r)
{
	return out << r.x << "\t" << r.y << "\t" << r.z << "\t";
}

/***********************************************************************************************************************
*** Quaternion -- orientation or rotation in 3D space
***********************************************************************************************************************/

template<typename T> struct Quaternion final
{
	Quaternion() : w(T()), x(T()), y(T()), z(T())
	{
	}

	template <typename U> Quaternion(Quaternion<U> const& r) : w(T(r.w)), x(T(r.x)), y(T(r.y)), z(T(r.z))
	{
	}

	Quaternion(T const& r, T const& s, T const& t, T const& u) : w(r), x(s), y(t), z(u)
	{
	}

	Quaternion(T const& r, Vector<T> const& s) : w(r), x(s.x), y(s.y), z(s.z)
	{
	}

	template <typename U> Quaternion& operator=(Quaternion<U> const& r)
	{
		w = T(r.w);
		x = T(r.x);
		y = T(r.y);
		z = T(r.z);

		return *this;
	}

	Vector<T> operator()(Vector<T> const& r)
	{
		auto ww = w * w;
		auto wx = w * x;
		auto wy = w * y;
		auto wz = w * z;
		auto xx = x * x;
		auto xy = x * y;
		auto xz = x * z;
		auto yy = y * y;
		auto yz = y * z;
		auto zz = z * z;

		return Vector<T>(
			r.x * (ww + xx - yy - zz) + 2 * (r.y * (xy - wz) + r.z * (xz + wy)),
			r.y * (ww - xx + yy - zz) + 2 * (r.z * (yz - wx) + r.x * (xy + wz)),
			r.z * (ww - xx - yy + zz) + 2 * (r.x * (xz - wy) + r.y * (yz + wx)));
	}

	Vector<T> vector() const
	{
		return Vector<T>(x, y, z);
	}

	T w, x, y, z;
};

//**********************************************************************************************************************

template <typename T> Quaternion<T> operator*(Quaternion<T> const& r, Quaternion<T> const& s)
{
	return Quaternion<T>(
		r.w * s.w - r.x * s.x - r.y * s.y - r.z * s.z,
		r.w * s.x + r.x * s.w + r.y * s.z - r.z * s.y,
		r.w * s.y + r.y * s.w + r.z * s.x - r.x * s.z,
		r.w * s.z + r.z * s.w + r.x * s.y - r.y * s.x);
}

template <typename T> Quaternion<T> operator*(T const& r, Quaternion<T> const& s)
{
	return Quaternion<T>(r * s.w, r * s.x, r * s.y, r * s.z);
}

template <typename T> Quaternion<T> operator*(Quaternion<T> const& r, T const& s)
{
	return Quaternion<T>(r.w * s, r.x * s, r.y * s, r.z * s);
}

template <typename T> Quaternion<T> operator/(Quaternion<T> const& r, T const& s)
{
	return Quaternion<T>(r.w / s, r.x / s, r.y / s, r.z / s);
}

template <typename T> T abs(Quaternion<T> const& r)
{
	return sqrt(r.w * r.w + r.x * r.x + r.y * r.y + r.z * r.z);
}

template <typename T> Quaternion<T> conjugate(Quaternion<T> const& r)
{
	return Quaternion<T>(r.w, -r.vector());
}

template <typename T> Quaternion<T> exp(Quaternion<T> const& r)
{
	return exp(r.w) * Quaternion<T>(cos(abs(r.vector())), normalize(r.vector()) * sin(abs(r.vector())));
}

template <typename T> Quaternion<T> inverse(Quaternion<T> const& r)
{
	return conjugate(r) / (r.w * r.w + r.x * r.x + r.y * r.y + r.z * r.z);
}

template <typename T> Quaternion<T> log(Quaternion<T> const& r)
{
	return Quaternion<T>(log(abs(r)), r.vector() / abs(r.vector()) * acos(r.w / abs(r)));
}

template <typename T> Quaternion<T> normalize(Quaternion<T> const& r)
{
	return r / abs(r);
}

template <typename T> Quaternion<T> pow(Quaternion<T> const& r, T const& s)
{
	return exp(log(r) * s);
}

template <typename T> Quaternion<T> pow(Quaternion<T> const& r, Quaternion<T> const& s)
{
	return exp(log(r) * s);
}

template <typename T> std::ostream& operator<<(std::ostream& out, Quaternion<T> const& r)
{
	return out << r.w << "\t" << r.x << "\t" << r.y << "\t" << r.z << "\t";
}

/***********************************************************************************************************************
*** Geometry3D
***********************************************************************************************************************/

/* TODO:  Euler to Quaternion conversions */

//**********************************************************************************************************************
