#ifndef __AURA_OF_POWER_H__
#define __AURA_OF_POWER_H__
#include "ritual.h"


class Aura_O_P : public Ritual {
    public:
    Aura_O_P();
    void notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) override;
};

#endif
