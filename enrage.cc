#include "enrage.h"
#include "ascii_graphics.h"

Enrage::Enrage():
    Enchantment{"Enrage", 2, "", "*2", "-2"} {}

void Enrage::set_next(std::shared_ptr<Component> next_c){
    s = bounded;
    next = next_c;
    add_atk = next_c->get_attack();
}

int Enrage::get_attack() const{
    return next->get_attack() + add_atk;
}

int Enrage::get_defence() const{
    return next->get_defence() - 2;
}

card_template_t Enrage::print() const{
        if (s == bounded){
                return next->print(get_attack(),get_defence(),get_acti_cost());
        }
        return display_enchantment_attack_defence(card_name,magic_cost, desc, "*2", "-2");
}

std::vector<card_template_t> Enrage::get_inspect_list() const{
        std::vector<card_template_t> res = next->get_inspect_list();
        res.emplace_back(display_enchantment_attack_defence(card_name,magic_cost,desc, "*2", "-2"));
        return res;
}
