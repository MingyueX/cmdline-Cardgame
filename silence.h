#ifndef __SILENCE_H__
#define __SILENCE_H__
#include "enchantment.h"


class Silence : public Enchantment {
    public:
    Silence();
    void activate(Board* board, playernum whoactivated, int me) override;
    void activate(Board* board, playernum whoactivated, int me, playernum tgt_player, int tgt) override;
};

#endif
