#ifndef __INP_H__
#define __INP_H__

#include <memory>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


class Inp{
    std::ifstream fin;
    bool using_file;
    bool fail_bit;
    public:
    Inp(bool use_file, std::string filename = "");
    bool use_file() const;
    bool getline(std::string& s);
    bool fail() const;
};

#endif
