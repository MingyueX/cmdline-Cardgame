#ifndef __UNSUMMON_H__
#define __UNSUMMON_H__

#include "spell.h"

class Unsummon : public Spell {
    public:
    Unsummon();
    void cast(Board* b, playernum whoplayed, playernum tgt_player, int n);
};

#endif
