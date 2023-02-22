#include <iostream>
#include <fstream>
#include <bit>
#include <numeric>

#include "fft.hpp"
#include "slr.h"

int main() {
    // Load all data
    std::ifstream inputFile("data.dat");

    uint32_t n;
    std::string s;
    inputFile >> s >> n;

    slr::series x(n);
    slr::series y(n);

    for (uint32_t i = 0; i < n; ++i) {
        inputFile >> x[i] >> y[i];
    }

    inputFile.close();

    // Find linear trend and subtract

    auto [a, b] = slr::slr(x, y);

    for (uint32_t i = 0; i < n; ++i) {
        y[i] -= a * x[i] + b;
    }

    // Series centering

    double mean_y = std::accumulate(y.begin(), y.end(), 0.) / (double) n;

    for (uint32_t i = 0; i < n; ++i) {
        y[i] -= mean_y;
    }

    // Output centered series

    std::ofstream centeredFile("centered.dat");

    centeredFile << "# " << n << std::endl;

    for (uint32_t i = 0; i < n; ++i) {
        centeredFile << std::fixed << std::setprecision(10) << std::setw(15) << x[i]<<std::setw(15) << y[i] << std::endl;
    }

    return 0;
}
