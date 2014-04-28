#pragma once

#include "Board.hh"
#include "consts.hh"
#include "utils.hh"

#include <cstdlib>
#include <string>
#include <iostream>
#include <locale>

void afficherMenu();
void toLowerCase(std::string &s);
GameState menu(Board *model, int &lifes);
void printModel(Board *model, int lifes, const int &charSet);
int textMain(int charSet);
