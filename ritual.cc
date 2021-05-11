#include "ritual.h"
#include "ascii_graphics.h"

Ritual::Ritual(std::string card_name, int magic_cost, 
               std::string desc, int charge, int acti_cost):
        Card{card_name, magic_cost, type_ritual, desc}, 
        charge{charge}, acti_cost{acti_cost} {}

card_template_t Ritual::print() const{
       return display_ritual(card_name,magic_cost,acti_cost,desc,charge);
}

int Ritual::get_acti_cost() {
       return acti_cost;
}

int Ritual::get_charge() {
       return charge;
}

void Ritual::change_charge(int n) {
       charge += n;
}

void Ritual::display(std::shared_ptr<Xwindow> GD, int x, int y) const {
       GD->fillRectangle(x, y, 150, 120, Xwindow::IndianRed);
       GD->drawString(x+5, y+13, card_name, Xwindow::White);
       GD->fillRectangle(x+150-15, y, 15, 23, Xwindow::White);
       GD->drawString(x+150-11, y+13, std::to_string(magic_cost), Xwindow::IndianRed);
       GD->fillRectangle(x, y+23, 150, 2, Xwindow::LightGray);
       GD->drawString(x+5, y+38, "Ritual", Xwindow::White);
       GD->fillRectangle(x, y+46, 150, 2, Xwindow::LightGray);
       unsigned int count = 0;
       int delta = 0;
       GD->fillRectangle(x, y+50, 23, 23, Xwindow::White);
       GD->drawString(x+5, y+60, std::to_string(acti_cost), Xwindow::IndianRed);
       int z = x+26;
       while (count < desc.size()) {
              GD->drawString(z, y+60 + delta, desc.substr(count, 20), Xwindow::White);
              delta += 13;
              count += 20;
       }
       GD->fillRectangle(x+150-23, y+120-23, 23, 23, Xwindow::White);
       GD->drawString(x+150-17, y+120-10, std::to_string(charge), Xwindow::IndianRed);
}
