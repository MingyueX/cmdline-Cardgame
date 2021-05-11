#include "dark_ritual.h"
#include "board.h"

Dark_R::Dark_R():
    Ritual{"Dark Ritual", 0,
           "At the start of your turn, gain 1 magic", 5, 1} {}

void Dark_R::notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) {
    if (event == turn_start) {
        if (current == owner) {
            board->addMag(owner, 1);
            this->change_charge(-this->get_acti_cost());
        }
    }
}
