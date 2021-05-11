#include "recharge.h"
#include "board.h"

Recharge::Recharge():
        Spell{"Recharge", 1, 
              "Your ritual gains 3 charges"} {}

void Recharge::cast(Board* b, playernum whoplayed){
        try{
                b->change_charge(whoplayed, 3);
        }
        catch(Ritual_DNE& e){
                throw CannotCast{"Cannot cast Recharge: you have no ritual."};
        }
}
