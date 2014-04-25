#include "Square.hh"

void Square::retain()
{
   Retain_count++;
}

void Square::release()
{
   if (Retain_count == 1)
      delete this;
   else
      Retain_count--;
}

Square::~Square()
{}

