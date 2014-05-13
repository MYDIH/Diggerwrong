#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <map>

const double LINE = 6;
// doit être > 0 ; plus c'est grand plus la fonction est linéaire
double inv(double x);
void splitStdString(const std::string &dataToSplit, char delim, std::vector<std::string> & resVect);
void parseFile(std::map<std::string, std::string> &result, const std::string &path);

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
