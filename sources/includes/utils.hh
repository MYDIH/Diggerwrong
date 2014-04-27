#pragma once

#include <string>
#include <sstream>
#include <utility>

// doit être > 0 ; plus c'est grand plus la fonction est linéaire
const double LINE = 6;

double inv(double x);

template<typename T>
std::string typeToString(T x)
{
    std::ostringstream flux;
    flux << x;

    return flux.str();
}
