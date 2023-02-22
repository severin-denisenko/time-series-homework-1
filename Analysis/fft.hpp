//
// Created by Severin on 22.02.2023.
//

#ifndef SPECTRALANALYSIS_FFT_HPP
#define SPECTRALANALYSIS_FFT_HPP

#include <vector>
#include <complex>
#include <cstdint>

namespace fft{
    using series = std::vector<std::complex<double>>;

    void fft(series& input, series& result, bool forward);
}

#endif //SPECTRALANALYSIS_FFT_HPP
