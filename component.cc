#include "component.h"
#include "ascii_graphics.h"

Component::Component(std::string card_name, int magic_cost, card_type type, std::string desc):
    Card{card_name, magic_cost, type, desc} {}

card_template_t Component::inspect() const{
    std::vector<card_template_t> cards = get_inspect_list();
    card_template_t result = cards.at(0);
    int col = 0;
    card_template_t row = {};
    for (size_t i = 1; i < cards.size(); i ++){
        if (col == 5){
            result = append(result,row);
            row = card_template_t{};
            col = 0;
        }
        row = row + cards.at(i);
        col += 1;
    }
    result = append(result,row);
    return result;
}
/*
void Component::displayMinion(std::shared_ptr<Xwindow> GD, int x, int y) {
    std::string desc;
    std::string name;
    if (this->get_type() == type_minion) {
    desc = this->get_desc();
    name = this->get_name();
    } else {
    desc = this->get_base()->get_desc();
    name = this->get_base()->get_name();
    }
    GD->fillRectangle(x, y, 150, 120, Xwindow::White);
    GD->drawString(x+5, y+13, name, Xwindow::LSGray);
    GD->fillRectangle(x+150-15, y, 15, 23, Xwindow::LightBlue);
    GD->drawString(x+150-11, y+13, std::to_string(this->get_cost()), Xwindow::LSGray);
    GD->fillRectangle(x, y+23, 150, 2, Xwindow::LSGray);
    GD->drawString(x+5, y+38, "Minion", Xwindow::LSGray);
    GD->fillRectangle(x, y+46, 150, 2, Xwindow::LSGray);
    int count = 0;
    int delta = 0;
    if (this->get_acti_cost()) {
        GD->fillRectangle(x, y+48, 23, 23, Xwindow::LightBlue);
        GD->drawString(x+5, y+60, std::to_string(this->get_acti_cost()), Xwindow::LSGray);
        int z = x+30;
        while (count < desc.size()) {
            GD->drawString(z, y+60 + delta, desc.substr(count, 20), Xwindow::LSGray);
            delta += 13;
            count += 20;
        }
    } else {
        while (count < desc.size()) {
            GD->drawString(x+5, y+60 + delta, desc.substr(count, 24), Xwindow::LSGray);
            delta += 13;
            count += 24;
        }
    }
    GD->fillRectangle(x, y+120-23, 23, 23, Xwindow::LightBlue);
    GD->drawString(x+5, y+120-10, std::to_string(this->get_attack()), Xwindow::LSGray);
    GD->fillRectangle(x+150-23, y+120-23, 23, 23, Xwindow::LightBlue);
    GD->drawString(x+150-17, y+120-10, std::to_string(this->get_defence()), Xwindow::LSGray);
}
*/
