
#pragma once

#include <cmath>

/***********************************************************************************************************************
*** RegressionAccumulator -- rewindable two variable linear regression
***********************************************************************************************************************/

class RegressionAccumulator final
{
    size_t count;
    double mean_x;
    double mean_y;
    double variance_x;
    double covariance;

public:
    RegressionAccumulator() noexcept : count(0), mean_x(0), mean_y(0), variance_x(0), covariance(0)
    {
    }

    RegressionAccumulator(const RegressionAccumulator& r) noexcept : count(r.count), mean_x(r.mean_x), mean_y(r.mean_y), variance_x(r.variance_x), covariance(r.covariance)
    {
    }

    RegressionAccumulator& operator=(const RegressionAccumulator& r) noexcept
    {
        count = r.count;
        mean_x = r.mean_x;
        mean_y = r.mean_y;
        variance_x = r.variance_x;
        covariance = r.covariance;
        return *this;
    }

    RegressionAccumulator& clear() noexcept
    {
        count = 0;
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
        ++count;
        mean_x += dx / count;
        mean_y += dy / count;
        variance_x += dx * (x - mean_x);
        covariance += dx * (y - mean_y);
        return *this;
    }

    RegressionAccumulator& remove(double x, double y) noexcept
    {
        if (count > 1)
        {
            double dx = x - mean_x;
            double dy = y - mean_y;
            --count;
            mean_x -= dx / count;
            mean_y -= dy / count;
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
        return count;
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
    size_t count;
    double mean_x;
    double variance_x;

public:
    StatisticsAccumulator() noexcept : count(0), mean_x(0), variance_x(0)
    {
    }

    StatisticsAccumulator(const StatisticsAccumulator& r) noexcept : count(r.count), mean_x(r.mean_x), variance_x(r.variance_x)
    {
    }

    StatisticsAccumulator& operator=(const StatisticsAccumulator& r) noexcept
    {
        count = r.count;
        mean_x = r.mean_x;
        variance_x = r.variance_x;
        return *this;
    }

    StatisticsAccumulator& clear() noexcept
    {
        count = 0;
        mean_x = 0;
        variance_x = 0;
        return *this;
    }

    StatisticsAccumulator& insert(double x) noexcept
    {
        double dx = x - mean_x;
        ++count;
        mean_x += dx / count;
        variance_x += dx * (x - mean_x);
        return *this;
    }

    StatisticsAccumulator& remove(double x) noexcept
    {
        if (count > 1)
        {
            double dx = x - mean_x;
            --count;
            mean_x -= dx / count;
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
        return count;
    }

    double stdev_p() const noexcept
    {
        return count > 0 && variance_x >= 0 ? std::sqrt(variance_x / count) : 0;
    }

    double stdev_s() const noexcept
    {
        return count > 1 && variance_x >= 0 ? std::sqrt(variance_x / (count - 1)) : 0;
    }

    double sum() const noexcept
    {
        return count * mean_x;
    }

    double variance() const noexcept
    {
        return count > 0 && variance_x >= 0 ? variance_x / count : 0;
    }
};

//**********************************************************************************************************************
