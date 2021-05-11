#ifndef __RECHARGE_H__
#define __RECHARGE_H__

#include "spell.h"

class Recharge : public Spell {
    public:
    Recharge();
    void cast(Board* b, playernum whoplayed) override;
};

#endif
