#pragma once
#include "figure.h"
#include "pentagon.h"
#include "hexagon.h"
#include "octagon.h"
#include <vector>
#include <memory>


class  sub {
public:
   virtual void Print(std::vector<std::shared_ptr<figure>>& v) = 0;

};
