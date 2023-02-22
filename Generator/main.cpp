//
// Created by Severin on 22.02.2023.
//

#include <fstream>
#include <cstdint>
#include <cmath>
#include <random>
#include <iomanip>

double alpha = 0.1;
double betta = 0.05;
double gamma = 0.5;
double phi = 0;
double A = 1;
double mu = 0.1;
double sigma = sqrt(A * A / (2 * gamma));

std::random_device randomDevice{};
std::mt19937 generator{randomDevice()};
std::normal_distribution<> normalDistribution{0, 1};

double f(double t){
    return alpha + betta * t + A * cos(2 * M_PI * mu * t + phi) + sigma * normalDistribution(generator);
}

int main(){
    double dt = 1;
    uint32_t N = 230;

    std::ofstream data("data.dat");

    data << "# " << N << std::endl;

    for (uint32_t i = 0; i < N; ++i) {
        double t = i * dt;
        data << std::fixed << std::setprecision(10) << std::setw(15) << t << std::setw(15) << f(t) << std::endl;
    }

    data.close();

    return 0;
}
