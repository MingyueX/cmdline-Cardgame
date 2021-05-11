#ifndef __CARD_H__
#define __CARD_H__
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "window.h"

class Xwindow;

typedef std::vector<std::string> card_template_t;


enum card_type : int{
    type_minion = 0,
    type_enchantment = 1,
    type_ritual = 2,
    type_spell = 3
};

class Card {
    protected:
    std::string card_name;
    int magic_cost;
    card_type type;
    std::string desc; //description of card ability //for print

    public:
    //ctor
    Card(std::string card_name, int magic_cost, card_type type, std::string desc);
    virtual ~Card();
    virtual void display(std::shared_ptr<Xwindow> GD, int x, int y) const  = 0;
    int get_cost() const;
    card_type get_type() const;
    virtual card_template_t print() const = 0;
    std::string get_name() const;
    std::string get_desc() const;

};

std::ostream& operator<<(std::ostream& os, const Card & c);

#endif
