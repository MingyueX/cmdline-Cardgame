#ifndef __DISENCHANT_H__
#define __DISENCHANT_H__

#include "spell.h"

class Disenchant : public Spell {
    public:
    Disenchant();
    void cast (Board* b, playernum whoplayed, playernum tgt_player, int n) override;
};

#endif
