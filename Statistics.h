
/*
MIT License

Copyright(c) 2020 Risto Lankinen

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
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
*** RegressionAccumulator -- rewindable two variable linear regression and correlation
***********************************************************************************************************************/

template <typename T = double> struct RegressionAccumulator final
{
    RegressionAccumulator() noexcept : n(0), mean_x(0), mean_y(0), variance_x(0), variance_y(0), covariance(0)
    {
    }

    RegressionAccumulator(const RegressionAccumulator& r) noexcept : n(r.n), mean_x(r.mean_x), mean_y(r.mean_y), variance_x(r.variance_x), variance_y(r.variance_y), covariance(r.covariance)
    {
    }

    RegressionAccumulator& operator=(const RegressionAccumulator& r) noexcept
    {
        n = r.n;
        mean_x = r.mean_x;
        mean_y = r.mean_y;
        variance_x = r.variance_x;
        variance_y = r.variance_y;
        covariance = r.covariance;
        return *this;
    }

    RegressionAccumulator& clear() noexcept
    {
        n = 0;
        mean_x = 0;
        mean_y = 0;
        variance_x = 0;
        variance_y = 0;
        covariance = 0;
        return *this;
    }

    RegressionAccumulator& insert(T const& x, T const& y) noexcept
    {
        ++n;
        auto dx = x - mean_x;
        auto dy = y - mean_y;
        mean_x = mean_x + dx / n;
        mean_y = mean_y + dy / n;
        variance_x = variance_x + dx * (x - mean_x);
        variance_y = variance_y + dy * (y - mean_y);
        covariance = covariance + dx * (y - mean_y);
        return *this;
    }

    RegressionAccumulator& remove(T const& x, T const& y) noexcept
    {
        if (n > 1)
        {
            --n;
            auto dx = x - mean_x;
            auto dy = y - mean_y;
            mean_x = mean_x - dx / n;
            mean_y = mean_y - dy / n;
            variance_x = variance_x - dx * (x - mean_x);
            variance_y = variance_y - dy * (y - mean_y);
            covariance = covariance - dx * (y - mean_y);
        }
        else clear();
        return *this;
    }

    T bias() const noexcept
    {
        return mean_y - mean_x * gain();
    }

    T correlation() const noexcept
    {
        return covariance / sqrt(variance_x * variance_y);
    }

    T gain() const noexcept
    {
        return covariance / variance_x;
    }

    T operator()(T const& x) const noexcept  // Get linearly correlated 'y' for a given 'x'
    {
        return (x - mean_x) * gain() + mean_y;
    }

    T inv(T const& y) const noexcept  // Get linearly correlated 'x' for a given 'y'
    {
        return (y - mean_y) / gain() + mean_x;
    }

    int samples() const noexcept
    {
        return n;
    }

private:
    size_t n;
    T mean_x;
    T mean_y;
    T variance_x;
    T variance_y;
    T covariance;
};

/***********************************************************************************************************************
*** StatisticsAccumulator -- rewindable single variable windowed average and standard deviation
***********************************************************************************************************************/

template <typename T = double> struct StatisticsAccumulator final
{
    StatisticsAccumulator() noexcept : n(0), mean_x(0), variance_x(0)
    {
    }

    StatisticsAccumulator(const StatisticsAccumulator& r) noexcept : n(r.n), mean_x(r.mean_x), variance_x(r.variance_x)
    {
    }

    StatisticsAccumulator& operator=(const StatisticsAccumulator& r) noexcept
    {
        n = r.n;
        mean_x = r.mean_x;
        variance_x = r.variance_x;
        return *this;
    }

    StatisticsAccumulator& clear() noexcept
    {
        n = 0;
        mean_x = 0;
        variance_x = 0;
        return *this;
    }

    StatisticsAccumulator& insert(T const& x) noexcept
    {
        ++n;
        auto dx = x - mean_x;
        mean_x = mean_x + dx / n;
        variance_x = variance_x + dx * (x - mean_x);
        return *this;
    }

    StatisticsAccumulator& remove(T const& x) noexcept
    {
        if (n > 1)
        {
            --n;
            auto dx = x - mean_x;
            mean_x = mean_x - dx / n;
            variance_x = variance_x - dx * (x - mean_x);
        }
        else clear();
        return *this;
    }

    T average() const noexcept
    {
        return mean_x;
    }

    T stdev_p() const noexcept
    {
        return sqrt(variance_p());
    }

    T stdev_s() const noexcept
    {
        return sqrt(variance_s());
    }

    T sum() const noexcept
    {
        return n * average();
    }

    T variance_p() const noexcept
    {
        return variance_x / n;
    }

    T variance_s() const noexcept
    {
        return variance_x / (n - 1);
    }

    int samples() const noexcept
    {
        return n;
    }

private:
    size_t n;
    T mean_x;
    T variance_x;
};

//**********************************************************************************************************************
