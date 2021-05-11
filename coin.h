#ifndef __COIN_H__
#define __COIN_H__

#include "spell.h"

class Coin : public Spell {
    public:
    Coin();
    void cast(Board* b, playernum whoplayed) override;
};

#endif
