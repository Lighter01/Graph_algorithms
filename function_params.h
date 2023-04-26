#ifndef FUNCTION_PARAMS_H
#define FUNCTION_PARAMS_H

#include <bitset>
#include <vector>
#include <random>
#include <cmath>


///TODO: add switch case for function choosing
namespace fn
{
    extern std::random_device rng;
    extern std::mt19937 gen;
    extern double function_real(const std::vector<double>& x_i);
    extern const double EulerConstant;
}

#endif // FUNCTION_PARAMS_H
