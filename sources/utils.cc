#include "utils.hh"

#include <iostream>
#include <stdexcept>

double inv(double x)
{
    return -(LINE)/(x+(LINE))+1;
}




void splitStdString(const std::string &dataToSplit, char delim, std::vector<std::string> & resVect)
{
    std::stringstream stream(dataToSplit);
    std::string tmp;

    while(std::getline(stream, tmp, delim))
        if(tmp.length() != 0)
            resVect.push_back(tmp);
}

bool parseFile(std::map<std::string, std::string> &result, const std::string &path)
{
    std::ifstream f;
    std::string tmp = "";
    std::vector<std::string> tmpVect;

    std::cout << path << "\n\n";
//    exit(1);

    f.open(path.c_str());

    if(f.is_open())
    {
       while(f.good())
       {
	  std::getline(f, tmp);
	  std::cout << tmp << std::endl;
	  splitStdString(tmp, '=', tmpVect);
	  if(tmpVect.size() == 2)
	     result.insert(std::pair<std::string, std::string>(tmpVect[0], tmpVect[1]));
	  tmpVect.clear();
       }

       return true;
    }
    else
       return false;
}

void setColorMask(sf::Image &image, const sf::Color &color, const sf::Color &replace)
{
    for(unsigned i = 0; i<image.GetWidth(); i++)
        for(unsigned j = 0; j<image.GetHeight(); j++)
            if(image.GetPixel(i, j) == color)
                image.SetPixel(i, j, replace);
}
