#include "fire_elemental.h"
#include "ascii_graphics.h"
#include "board.h"

Fire_ele::Fire_ele():
    Minion{"Fire elemental", 2, 
           "Whenever an opponent's minion enters play, deal 1 damage to it", 
           2, 2} {}


void Fire_ele::notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) {
    if (event == min_in) {
        if (n_owner != t_owner) {
            board->change_atk_hp(0, -1, t_owner, tgt);
        }
    }
}

card_template_t Fire_ele::print() const{
       return display_minion_triggered_ability(card_name,magic_cost,attack,defence, desc);
}

card_template_t Fire_ele::print(int atk, int def, int activ_cost) const{
       return display_minion_triggered_ability(card_name,magic_cost,atk,def, desc);
}
