//
// Created by Severin on 22.02.2023.
//

#include "fft.hpp"

namespace fft{
    std::complex<double> W(uint32_t q, uint32_t p, int8_t sign);
    void recursive_fft(series& input, series& result, bool forward);
    void iterative_dft(const series& input, series& result, bool forward);

    inline bool is_power_of_tho(uint32_t x)
    {
        return (x & (x - 1)) == 0;
    }

    /*
     * Performs fast Furrier transform
     */
    void fft(series &input, series &result, bool forward)
    {
        uint32_t n = input.size();
        if (!is_power_of_tho(n)){
            throw std::runtime_error("Can't perform fast Furrier transform on time series length not power of tho");
        }
        double n_inverse_sqrt = 1 / sqrt((double) n);

        recursive_fft(input, result, forward);

        for (uint32_t i = 0; i < n; ++i)
        {
            result.at(i) *= n_inverse_sqrt;
        }
    }

    void iterative_dft(const series& input, series& result, bool forward)
    {
        uint32_t N = input.size();
        int8_t sign = forward ? -1 : 1;

        for (uint32_t k = 0; k < N; ++k)
        {
            for (uint32_t n = 0; n < N; ++n)
            {
                result.at(k) += input.at(n) * W(n * k, N, sign);
            }
        }
    }

    void recursive_fft(series& input, series& result, bool forward)
    {
        uint32_t n = input.size();

        if (n < 64){
            iterative_dft(input, result, forward);
            return;
        }

        series even_input(n/2);
        series even_result(n/2);

        series odd_input(n/2);
        series odd_result(n/2);

        for (uint32_t i = 0; 2 * i < n; i++) {
            even_input.at(i) = input.at(2 * i);
            odd_input.at(i) = input.at(2 * i + 1);
        }

        recursive_fft(even_input, even_result, forward);
        recursive_fft(odd_input, odd_result, forward);

        for (uint32_t i = 0; 2 * i < n; ++i)
        {
            result.at(2 * i) = even_result.at(i);
            result.at(2 * i + 1) = odd_result.at(i);
        }

        for (uint32_t i = 0; 2 * i < n; ++i)
        {
            result.at(i) = even_result.at(i) + odd_result.at(i) * W(i, n, forward? -1: 1);
            result.at(i + n/2) = even_result.at(i) + odd_result.at(i) * W(i + n/2, n, forward? -1: 1);
        }
    }

    inline std::complex<double> W(uint32_t q, uint32_t p, int8_t sign)
    {
        return std::exp(sign * 2 * M_PI * std::complex(0.0, 1.0) * (double) q / (double) p);
    }
}
