#include "banish.h"
#include "board.h"


Banish::Banish():
        Spell{"Banish", 2, 
             "Destroy target minion or ritual"} {}

void Banish::cast(Board* b, playernum whoplayed, playernum tgt_player, int n) {
        try {
                b->kill(tgt_player,n);
        } catch(Ritual_DNE& e) {
                throw CannotCast{"cannot cast banish: no ritual at target"};
        } catch(Minion_DNE& e) {
                throw CannotCast{"cannot cast banish: no minion at target"};
        }
}
