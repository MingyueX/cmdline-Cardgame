#include "silence.h"

Silence::Silence():
    Enchantment{"Silence", 1,
                "Enchanted minion cannot use abilities"}{}

void Silence::activate(Board* board, playernum whoactivated, int me){
    throw Cannot_activate{"This minion is silenced, so it cannot be activated."};
}
void Silence::activate(Board* board, playernum whoactivated, int me, playernum tgt_player, int tgt){
    throw Cannot_activate{"This minion is silenced, so it cannot be activated."};
}
