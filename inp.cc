#include "inp.h"


Inp::Inp (bool use_file, std::string filename):
    fail_bit{false}
    {
    using_file = use_file;
    if (using_file){
        fin.open(filename);
        if (fin.fail()){ //cannot open file.
            using_file = false;
        }
    }
}

bool Inp::getline(std::string& s){
    if (using_file){
        if (! std::getline(fin,s)){
            using_file = false;
        }
    }
    if (! using_file){
        if (! std::getline(std::cin, s)){
            fail_bit = true;
            return false;
        }
    }
    return true;
}

bool Inp::fail() const{
    return fail_bit;
}

bool Inp::use_file() const{
    return using_file;
}
