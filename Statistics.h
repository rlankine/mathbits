
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

#include <cmath>

/***********************************************************************************************************************
*** RegressionAccumulator -- rewindable two variable linear regression
***********************************************************************************************************************/

class RegressionAccumulator final
{
    size_t n;
    double mean_x;
    double mean_y;
    double variance_x;
    double covariance;

public:
    RegressionAccumulator() noexcept : n(0), mean_x(0), mean_y(0), variance_x(0), covariance(0)
    {
    }

    RegressionAccumulator(const RegressionAccumulator& r) noexcept : n(r.n), mean_x(r.mean_x), mean_y(r.mean_y), variance_x(r.variance_x), covariance(r.covariance)
    {
    }

    RegressionAccumulator& operator=(const RegressionAccumulator& r) noexcept
    {
        n = r.n;
        mean_x = r.mean_x;
        mean_y = r.mean_y;
        variance_x = r.variance_x;
        covariance = r.covariance;
        return *this;
    }

    RegressionAccumulator& clear() noexcept
    {
        n = 0;
        mean_x = 0;
        mean_y = 0;
        variance_x = 0;
        covariance = 0;
        return *this;
    }

    RegressionAccumulator& insert(double x, double y) noexcept
    {
        double dx = x - mean_x;
        double dy = y - mean_y;
        ++n;
        mean_x += dx / n;
        mean_y += dy / n;
        variance_x += dx * (x - mean_x);
        covariance += dx * (y - mean_y);
        return *this;
    }

    RegressionAccumulator& remove(double x, double y) noexcept
    {
        if (n > 1)
        {
            double dx = x - mean_x;
            double dy = y - mean_y;
            --n;
            mean_x -= dx / n;
            mean_y -= dy / n;
            variance_x -= dx * (x - mean_x);
            covariance -= dx * (y - mean_y);
        }
        else clear();
        return *this;
    }

    double bias() const noexcept
    {
        return mean_y - mean_x * gain();
    }

    double gain() const noexcept
    {
        return variance_x > 0 ? covariance / variance_x : 0;
    }

    int samples() const noexcept
    {
        return n;
    }

    double operator()(double x) const noexcept
    {
        return gain() * x + bias();
    }

    double inv(double y) const noexcept
    {
        return (y - bias()) / gain();
    }
};

/***********************************************************************************************************************
*** StatisticsAccumulator -- rewindable one variable running average, standard deviation, and variance
***********************************************************************************************************************/

class StatisticsAccumulator final
{
    size_t n;
    double mean_x;
    double variance_x;

public:
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

    StatisticsAccumulator& insert(double x) noexcept
    {
        double dx = x - mean_x;
        ++n;
        mean_x += dx / n;
        variance_x += dx * (x - mean_x);
        return *this;
    }

    StatisticsAccumulator& remove(double x) noexcept
    {
        if (n > 1)
        {
            double dx = x - mean_x;
            --n;
            mean_x -= dx / n;
            variance_x -= dx * (x - mean_x);
        }
        else clear();
        return *this;
    }

    double average() const noexcept
    {
        return mean_x;
    }

    int samples() const noexcept
    {
        return n;
    }

    double stdev_p() const noexcept
    {
        return n > 0 && variance_x >= 0 ? std::sqrt(variance_x / n) : 0;
    }

    double stdev_s() const noexcept
    {
        return n > 1 && variance_x >= 0 ? std::sqrt(variance_x / (n - 1)) : 0;
    }

    double sum() const noexcept
    {
        return n * mean_x;
    }

    double variance() const noexcept
    {
        return n > 0 && variance_x >= 0 ? variance_x / n : 0;
    }
};

//**********************************************************************************************************************
