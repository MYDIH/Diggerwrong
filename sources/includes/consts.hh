#pragma once

#include <vector>
#include <string>

const unsigned DECALAGE_CONSOLE = 35; // Distance entre Statu et Explications

const std::string CHARS[][8] = {{" ☠ ", "☾", "☽", " ☉ ", "+", "+", "|", ""},
                                {"\033[31;1m ☠ \033[0m", "\033[33m☾", "☽\033[0m", " ☉ ", "\033[30;1m+", "+\033[0m", "\033[30;1m|\033[0m", "\033[36m"},
                                {"\033[31;1m%%%\033[0m", "\033[33m{", "}\033[0m", "@@@", "\033[30;1m+", "+\033[0m", "\033[30;1m|\033[0m", "\033[36m"},
                                {"%%%", "{", "}", "@@@", "+", "+", "|", ""}};
