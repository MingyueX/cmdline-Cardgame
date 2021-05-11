#ifndef __RAISE_DEAD_H__
#define __RAISE_DEAD_H__

#include "spell.h"

class RaiseDead : public Spell {
    public:
    RaiseDead();
    void cast(Board* b, playernum whoplayed) override;
};

#endif
