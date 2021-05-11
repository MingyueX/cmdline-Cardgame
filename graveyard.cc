#include "graveyard.h"
#include "card.h"
#include "component.h"
#include "enchantment.h"
#include "minion.h"
#include "ascii_graphics.h"

Graveyard::Graveyard()
    :minions{}{}


bool Graveyard::isEmpty() const{
    return minions.size() == 0;
}

void Graveyard::display(std::shared_ptr<Xwindow> g, int x, int y) const{
    if (isEmpty()) {
        return;
    } else {
        minions.back()->display(g, x, y);
    }
}

std::shared_ptr<Component> Graveyard::pop(){
    if (isEmpty()) {
        throw Graveyard_empty{"The graveyard is empty"};
        return std::shared_ptr<Component>();
    }
    std::shared_ptr<Component> res = minions.back();
    minions.pop_back();
    return res;
}

void Graveyard::add(std::shared_ptr<Component> c){
    if (c->get_type() == type_minion){
        minions.push_back(c);
    } else {
        minions.push_back(std::dynamic_pointer_cast<Enchantment>(c)->get_base());
    }
}
card_template_t Graveyard::print() const{
    if (isEmpty()){
        return CARD_TEMPLATE_BORDER;
    }
    return minions.back()->print();
}

std::ostream& operator<<(std::ostream& os, const Component & h){
    os << h.print();
    return os;
}
