#include "delay.h"
Delay::Delay():
    Enchantment{"Delay", 1, 
                "Enchanted minion does not gain an action on their next turn. This enchantment is automatically destroyed after 1 turn"} {}


void Delay::set_act_pt(int n) {
    return;
}
