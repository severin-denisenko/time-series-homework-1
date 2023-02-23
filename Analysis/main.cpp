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
        centeredFile << std::fixed << std::setprecision(10) << std::setw(15) << x[i] <<
        std::setw(15) << y[i] << std::endl;
    }

    // Periodogram calculation

    uint32_t N = 2 * std::bit_ceil(n);

    fft::series fftInput(N);
    fft::series fftOutput(N);

    std::copy(y.begin(), y.end(), fftInput.begin());

    fft::fft(fftInput, fftOutput, true);

    slr::series periodogramX(N);
    slr::series periodogramY(N);

    for (uint32_t i = 0; i < N / 2; ++i) {
        periodogramY[i] =  1. / (N * N) * (fftOutput[i].real() * fftOutput[i].real() +
                fftOutput[i].imag() * fftOutput[i].imag());

        periodogramX[i] = i / (N * x[1]);
    }

    // Periodogram output

    std::ofstream periodogramFile("periodogram.dat");

    periodogramFile << "# " << N / 2 << std::endl;

    for (uint32_t i = 0; i < N / 2; ++i) {
        periodogramFile << std::fixed << std::setprecision(10) << std::setw(15) << periodogramX[i] <<
        std::setw(15) << periodogramY[i] << std::endl;
    }


    return 0;
}
