#pragma once

#include <string>
#include <sstream>
#include <utility>

const double LINE = 6;
// doit être > 0 ; plus c'est grand plus la fonction est linéaire
double inv(double x);

template<typename T>
std::string typeToString(T x)
{
   std::ostringstream flux;
   flux << x;

   return flux.str();
}


/*
  class Cloneable
  {
  public:
  virtual ~Cloneable();
  virtual Clonable* clone() const = 0;
  };
*/
