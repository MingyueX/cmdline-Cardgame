#include "unsummon.h"
#include "board.h"

Unsummon::Unsummon():
        Spell{"Unsummon", 1, 
             "Return target minion to its owner's hand"} {}

void Unsummon::cast(Board * b, playernum whoplayed, playernum tgt_player, int n){
        try{
                b->send_back(tgt_player, n);
        }
        catch(Minion_DNE& e){
                throw CannotCast{"cannot case unsummon. no minon at target."};
        }
}
