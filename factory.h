#pragma once
#include <memory>
#include <iostream>
#include <fstream>
#include "hexagon.h"
#include "octagon.h"
#include "pentagon.h"
#include <string>

struct factory {
    std::shared_ptr<figure> FigureCreate(std::istream& is);

    std::shared_ptr<figure> FigureCreateFile(std::ifstream& is);

};
