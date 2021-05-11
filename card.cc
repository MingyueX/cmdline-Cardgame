#include "card.h"
#include "ascii_graphics.h"

Card::Card(std::string card_name, 
           int magic_cost, card_type type, std::string desc):
    card_name{card_name}, magic_cost{magic_cost}, 
    type{type}, desc{desc} {}

Card::~Card() {}

int Card::get_cost() const{
       return magic_cost;
}

std::string Card::get_desc() const {
       return desc;
}

std::string Card::get_name() const {
       return card_name;
}

card_type Card::get_type() const {
       return type;
}

std::ostream& operator<<(std::ostream& os, const Card & c){
    os << c.print();
    return os;
}
