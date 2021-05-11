#include "coin.h"
#include "board.h"

Coin::Coin():
        Spell{"Coin", 0, 
             "Gain 1 magic"} {}

void Coin::cast(Board* b, playernum whoplayed) {
        b->addMag(whoplayed, 1);
}
