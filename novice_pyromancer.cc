#include "novice_pyromancer.h"
#include "ascii_graphics.h"
#include "board.h"

Novice_P::Novice_P():
    Minion{"Novice Pyromancer", 1, 
           "Deal 1 damage to target minion", 
           0, 1}, acti_cost{1} {}

void Novice_P::activate(Board* board, playernum whoactivated, int me, playernum tgt_player, int tgt){
    if (action_pt < 1){
        throw No_act_p{"this minion has no action point left"};
    }
    action_pt -= 1;
    try{
        board->change_atk_hp(0,-1, tgt_player, tgt);
    }
    catch(Minion_DNE& e){
        action_pt += 1;
        throw Cannot_activate{"Cannot activate Novice Pyromancer because target is not found. "};
    }
}

int Novice_P::get_acti_cost() const{
    return acti_cost;
}

card_template_t Novice_P::print() const{
       return display_minion_activated_ability(card_name,magic_cost,attack,defence, acti_cost, desc);
}

card_template_t Novice_P::print(int atk, int def, int activ_cost) const{
       return display_minion_activated_ability(card_name,magic_cost,atk,def, activ_cost, desc);
}
