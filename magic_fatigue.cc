#include "magic_fatigue.h"

Magic_F::Magic_F():
    Enchantment{"Magic Fatigue", 0,
                "Enchanted minion's activated ability costs 2 more"}{}

int Magic_F::get_acti_cost() const{
    return next->get_acti_cost() + 2;
}
