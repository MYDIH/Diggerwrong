#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <map>

#include <SFML/Graphics.hpp>

#define MAX(a,b) ( ((a)>(b)) ? (a) : (b) )

const double LINE = 6;
// doit être > 0 ; plus c'est grand plus la fonction est linéaire
double inv(double x);

void splitStdString(const std::string &dataToSplit, char delim, std::vector<std::string> & resVect);
bool parseFile(std::map<std::string, std::string> &result, const std::string &path);
void setColorMask(sf::Image &image, const sf::Color &color, const sf::Color &replace);

template<typename T>
std::string typeToString(T x)
{
   std::ostringstream flux;
   flux << x;

   return flux.str();
}

template<typename T>
void swap(T & a, T & b)
{
   const T tmp = a;
   a = b;
   b = tmp;
}


/*
  class Cloneable
  {
  public:
  virtual ~Cloneable();
  virtual Clonable* clone() const = 0;
  };
*/
