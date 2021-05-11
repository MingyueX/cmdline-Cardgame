#include "disenchant.h"
#include "board.h"

Disenchant::Disenchant():
        Spell{"Disenchant", 1, 
             "Destroy the top enchantment on target minion"} {}

void Disenchant::cast(Board* b, playernum whoplayed, playernum tgt_player, int n){
        try{
                b->remove_outer(tgt_player, n);
        }
        catch(Minion_DNE& e){
                throw CannotCast{"target does not exist"};
        }
        catch(No_enchantment& e){
                throw CannotCast{"target has no enchantment"};
        }
}
