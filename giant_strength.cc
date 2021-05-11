#include "giant_strength.h"
#include "ascii_graphics.h"

Giant_s::Giant_s():
    Enchantment{"Giant Strength", 1, "", "+2", "+2"} {}

int Giant_s::get_attack() const{
    return next->get_attack() + 2;
}

int Giant_s::get_defence() const{
    return next->get_defence() + 2;
}


card_template_t Giant_s::print() const{
        if (s == bounded){
                return next->print(get_attack(),get_defence(), get_acti_cost());
        }
        return display_enchantment_attack_defence(card_name,magic_cost, desc, "+2", "+2");
}

std::vector<card_template_t> Giant_s::get_inspect_list() const{
        std::vector<card_template_t> res = next->get_inspect_list();
        res.emplace_back(display_enchantment_attack_defence(card_name,magic_cost,desc, "+2", "+2"));
        return res;
}
