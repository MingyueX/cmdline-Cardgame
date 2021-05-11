#ifndef __BANISH_H__
#define __BANISH_H__

#include "spell.h"

class Banish : public Spell {
    public:
    Banish();
    void cast(Board* b, playernum whoplayed, playernum tgt_player, int n) override;
};

#endif
