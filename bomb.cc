#include "bomb.h"
#include "ascii_graphics.h"
#include "board.h"

Bomb::Bomb():
    Minion{"Bomb", 2, 
           "Deals damage to all the opponent minions equal to its attack value when it dies", 
           1, 2} {}

void Bomb::notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) {
    if (event == min_out) {
        if (n_owner == t_owner && notified+1 == tgt) {
            int atk = board->getMinion_atk(n_owner, notified+1);
            board->change_hp(-atk, other(n_owner));
        }
    }
}

card_template_t Bomb::print() const{
       return display_minion_triggered_ability(card_name,magic_cost,attack,defence, desc);
}

card_template_t Bomb::print(int atk, int def, int activ_cost) const{
       return display_minion_triggered_ability(card_name,magic_cost,atk,def, desc);
}
