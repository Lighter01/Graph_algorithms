#include "function_params.h"

#include <iostream>

namespace fn
{
    std::random_device rng;
    std::mt19937 gen(rng());

    double function_real(const std::vector<double> &x_i)
    {
        return std::pow(x_i[0], 3) + std::pow(x_i[1], 2) - 3 * x_i[0] - 2 * x_i[1] + 2; // x1^3 + x2^2 - 3*x1 - 2*x2 + 2
    }
    const double EulerConstant = std::exp(1.0);

}

