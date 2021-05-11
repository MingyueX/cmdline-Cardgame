#include <memory>

#include "ascii_graphics.h"
#include "bomb.h"
#include "dr_boom.h"
#include "board.h"

DrBoom::DrBoom():
    Minion{"Dr Boom", 4, "Summon up to two 1/2 bombs", 
           2, 2}, acti_cost{3} {}

int DrBoom::get_acti_cost() const{
    return acti_cost;
}

void DrBoom::activate(Board* board, playernum whoactivated, int me){
    if (action_pt < 1){
        throw No_act_p{"this minion has no action point left"};
    }
    action_pt -= 1;
    try{
        board->add_minion(whoactivated, std::dynamic_pointer_cast<Component>(std::make_shared<Bomb>()));
    }
    catch(No_space& e){
        action_pt += 1;
        throw Cannot_activate{"Cannot activate because the board is full. "};
    }
    try{
        board->add_minion(whoactivated, std::dynamic_pointer_cast<Component>(std::make_shared<Bomb>()));
    }
    catch(No_space& e){}
}

card_template_t DrBoom::print() const{
       return display_minion_activated_ability(card_name,magic_cost,attack,defence, acti_cost, desc);
}

card_template_t DrBoom::print(int atk, int def, int activ_cost) const{
       return display_minion_activated_ability(card_name,magic_cost,atk,def, activ_cost, desc);
}
