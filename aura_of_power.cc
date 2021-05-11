#include "aura_of_power.h"
#include "board.h"

Aura_O_P::Aura_O_P():
    Ritual{"Aura of Power", 1,
           "Whenever a minion enters play under your control, it gains +1/+1", 
           4, 1} {}

void Aura_O_P::notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) {
    if (event == min_in) {
        if (t_owner == owner) {
            if (this->get_charge() >= this->get_acti_cost()) {
                board->change_atk_hp(1, 1, owner, tgt);
                this->change_charge(-this->get_acti_cost());
            }
        }
    }
}
