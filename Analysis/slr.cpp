//
// Created by Severin on 22.02.2023.
//

#include "slr.h"

#include <numeric>

namespace slr{
    std::tuple<double, double> slr(const series& x, const series& y){
        if (x.size() != y.size())
            throw std::runtime_error("Can't perform linear regression on x and y different length");

        uint32_t n = x.size();

        double mean_x = std::accumulate(x.begin(), x.end(), 0.) / (double)x.size();
        double mean_y = std::accumulate(y.begin(), y.end(), 0.) / (double)y.size();

        double numerator = 0;
        double denominator = 0;

        for (uint32_t i = 0; i < n; ++i) {
            numerator += (x[i] - mean_x) * (y[i] - mean_y);
            denominator += (x[i] - mean_x) * (x[i] - mean_x);
        }

        double value = numerator / denominator;

        return {value, mean_y - mean_x * value};
    }
}
