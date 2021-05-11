#ifndef __FIRE__ELEMENTAL_H__
#define __FIRE__ELEMENTAL_H__
#include "minion.h"

class Fire_ele : public Minion {
    public:
    Fire_ele();
    void notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int aciv_cost) const override;
};

#endif
