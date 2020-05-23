#pragma once
#include "sub.h"
#include <string>
#include <fstream>
#include <time.h>
#include <string>



class ConsolePrint : public sub {
public:
   void Print(std::vector<std::shared_ptr<figure>>& v) override {
       for (unsigned int i = 0; i < v.size(); i++) {
           v[i]->print(std::cout);
       }
   }
};


class FilePrint : public sub {
private:
   unsigned int count = 1;

public:
   void Print(std::vector<std::shared_ptr<figure>>& v) override {
       std::string filename = "";
       filename = "out_" + std::to_string(count) + ".txt";
       count++;
       std::ofstream file(filename);
       for (unsigned int i = 0; i < v.size(); i++) {
           v[i]->printFile(file);
       }
   }

};
