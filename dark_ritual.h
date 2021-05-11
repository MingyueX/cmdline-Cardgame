#ifndef __DARK_RITUAL_H__
#define __DARK_RITUAL_H__
#include "ritual.h"


class Dark_R : public Ritual {
    public:
    Dark_R();
    void notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) override;
};

#endif
