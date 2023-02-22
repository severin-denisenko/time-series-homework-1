//
// Created by Severin on 22.02.2023.
//

#ifndef SPECTRALANALYSIS_SLR_H
#define SPECTRALANALYSIS_SLR_H

#include <vector>
#include <tuple>
#include <cstdint>

// Simple linear regression
namespace slr{
    using series = std::vector<double>;

    // Return a, b -- parameters of linear fit ax+b
    std::tuple<double, double> slr(const series& x, const series& y);
}

#endif //SPECTRALANALYSIS_SLR_H
