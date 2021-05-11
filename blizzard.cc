#include "blizzard.h"
#include "board.h"

Blizzard::Blizzard():
        Spell{"Blizzard", 3, 
             "Deal 2 damage to all minions"} {}

void Blizzard::cast(Board* b, playernum whoplayed) {
        b->change_all_hp(-2);
}
