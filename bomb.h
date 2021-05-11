#ifndef __BOMB_H__
#define __BOMB_H__
#include "minion.h"

class Bomb : public Minion {
    public:
    Bomb();
    void notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
};

#endif
