
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

#include <ostream>

/***********************************************************************************************************************
*** SummationOf<type> -- Pairwise summation of an arbitrary long stream of values in O(log(n)) space and O(n) time
***********************************************************************************************************************/

template <typename ValueType, typename IndexType = int> struct SummationOf final
{
    SummationOf() noexcept : index(0)
    {
    }

    SummationOf(SummationOf const &r)  noexcept : index(r.index)
    {
        for (int bit = 0; (IndexType(1) << bit) <= index; ++bit) if (index & (IndexType(1) << bit)) value[bit] = r.value[bit];
    }

    SummationOf(SummationOf const &r, SummationOf const &s) : index(r.index + s.index)
    {
        for (int bit = 0; (IndexType(1) << bit) <= index; ++bit)
        {
            if (r.index & (IndexType(1) << bit))
            {

            }
            if (s.index & (IndexType(1) << bit))
            {

            }
            throw nullptr; // TODO
        }
    }

    SummationOf(ValueType const &r) noexcept : index(0)
    {
        operator+=(r);
    }

    SummationOf &operator=(SummationOf const &r) noexcept
    {
        index = r.index;
        for (int bit = 0; (IndexType(1) << bit) <= index; ++bit) if (index & (IndexType(1) << bit)) value[bit] = r.value[bit];
        return *this;
    }

    SummationOf &operator=(ValueType const &r) noexcept
    {
        index = 0;
        return operator+=(r);
    }

    SummationOf &operator+=(ValueType r) noexcept
    {
        if (r == ValueType(0)) return *this;
        ++index;
        for (int bit = 0; (IndexType(1) << bit) <= index; ++bit)
        {
            if (index & (IndexType(1) << bit))
            {
                value[bit] = r;
                break;
            }
            r += value[bit];
        }
        return *this;
    }

    operator ValueType() const noexcept
    {
        ValueType result = 0;
        for (int bit = 0; (IndexType(1) << bit) <= index; ++bit) if (index & (IndexType(1) << bit)) result += value[bit];
        return result;
    }

    friend SummationOf operator+(SummationOf const &r, SummationOf const &s) noexcept
    {
        return SummationOf(r, s);
    }

    friend SummationOf operator+(SummationOf const &r, ValueType const &s) noexcept
    {
        return SummationOf(r, s);
    }

    friend SummationOf operator+(ValueType const &r, SummationOf const &s) noexcept
    {
        return SummationOf(s, r);
    }

    friend std::ostream &operator<<(std::ostream &out, SummationOf const &r)
    {
        return out << r.operator ValueType();
    }

private:
    ValueType value[sizeof(IndexType) * 8];
    IndexType index;
};
