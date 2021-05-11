#ifndef __STANDSTILL_H__
#define __STANDSTILL_H__
#include "ritual.h"


class Standstill : public Ritual {
    public:
    Standstill();
    void notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) override;
//    void notify(Board * board, Event event, playernum current, int minion_idx) override;
};

#endif
