#include "standstill.h"
#include "board.h"

Standstill::Standstill():
    Ritual{"Standstill", 3,
           "Whenever a minion enters play, destroy it", 
           4, 2} {}

void Standstill::notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) {
    if (event == min_in) {
        if (this->get_charge() >= this->get_acti_cost()) {
            board->kill(t_owner, tgt);
            this->change_charge(-this->get_acti_cost());
        }
    }
}
