#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__

#include "spell.h"

class Blizzard : public Spell {
    public:
    Blizzard();
    void cast(Board* b, playernum whoplayed) override;
};

#endif
