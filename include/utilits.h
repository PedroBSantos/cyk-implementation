#ifndef UTILITS_H
#define UTILITS_H

#include <vector>
#include <string>
#include <fstream>
#include <set>
#include <string.h>
#include "../include/grammar.h"
#include "split_string.h"

std::string showTable(std::vector<std::vector<std::string>>& table);
Grammar loadFile();

#endif