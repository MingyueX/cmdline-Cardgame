#ifndef __POTION_SELLER_H__
#define __POTION_SELLER_H__
#include "minion.h"

class Potion_S : public Minion {
    public:
    Potion_S();
    void notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
};

#endif
