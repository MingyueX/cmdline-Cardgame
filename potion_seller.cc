#include "potion_seller.h"
#include "ascii_graphics.h"
#include "board.h"

Potion_S::Potion_S():
    Minion{"Potion Seller", 2, 
           "At the end of your turn, all your minions gain +0/+1", 
           1, 3} {}

void Potion_S::notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) {
    if (event == turn_end){
        if (current == n_owner) {
            board->change_hp(1, n_owner);
        }
    }
}

card_template_t Potion_S::print() const{
       return display_minion_triggered_ability(card_name,magic_cost,attack,defence, desc);
}

card_template_t Potion_S::print(int atk, int def, int activ_cost) const{
       return display_minion_triggered_ability(card_name,magic_cost,atk,def, desc);
}
