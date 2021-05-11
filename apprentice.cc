#include <memory>
#include "ascii_graphics.h"
#include "apprentice.h"
#include "air_elemental.h"
#include "board.h"

Apprentice::Apprentice():
    Minion{"Apprentice Summoner", 1, "Summon a 1/1 air elemental", 
           1, 1}, acti_cost{1} {}

int Apprentice::get_acti_cost() const {
    return acti_cost;
}

void Apprentice::activate(Board* board, playernum whoactivated, int me) {
    if (action_pt < 1) {
        throw No_act_p{"this minion has no action point left"};
    }
    action_pt -= 1;
    try {
        board->add_minion(whoactivated, std::dynamic_pointer_cast<Component>(std::make_shared<Air_ele>()));
    } catch(No_space& e) {
        action_pt += 1;
        throw Cannot_activate{"Cannot activate because the board is full. "};
    }
}

card_template_t Apprentice::print() const {
       return display_minion_activated_ability(card_name,magic_cost,attack,defence, acti_cost, desc);
}

card_template_t Apprentice::print(int atk, int def, int activ_cost) const {
       return display_minion_activated_ability(card_name,magic_cost,atk,def, activ_cost, desc);
}
