#include <memory>

#include "ascii_graphics.h"
#include "air_elemental.h"
#include "master_summoner.h"
#include "board.h"

Master_S::Master_S():
    Minion{"Master Summoner", 3, "Summon up to three 1/1 air elementals", 
           2, 3}, acti_cost{2} {}

int Master_S::get_acti_cost() const{
    return acti_cost;
}

void Master_S::activate(Board* board, playernum whoactivated, int me){
    if (action_pt < 1){
        throw No_act_p{"this minion has no action point left"};
    }
    action_pt -= 1;
    try{
        board->add_minion(whoactivated, std::dynamic_pointer_cast<Component>(std::make_shared<Air_ele>()));
    }
    catch(No_space& e){
        action_pt += 1;
        throw Cannot_activate{"Cannot activate because the board is full. "};
    }
    try{
        board->add_minion(whoactivated, std::dynamic_pointer_cast<Component>(std::make_shared<Air_ele>()));
        board->add_minion(whoactivated, std::dynamic_pointer_cast<Component>(std::make_shared<Air_ele>()));
    }
    catch(No_space& e){}
}

card_template_t Master_S::print() const{
       return display_minion_activated_ability(card_name,magic_cost,attack,defence, acti_cost, desc);
}

card_template_t Master_S::print(int atk, int def, int activ_cost) const{
       return display_minion_activated_ability(card_name,magic_cost,atk,def, activ_cost, desc);
}
