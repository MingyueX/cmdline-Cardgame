#ifndef __NOVICE_PYROMANCER_H__
#define __NOVICE_PYROMANCER_H__
#include "minion.h"

class Novice_P : public Minion {
    int acti_cost;
    public:
    Novice_P();
    int get_acti_cost() const override;
    void activate(Board* board, playernum whoactivated, int me, playernum tgt_player, int tgt) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
};

#endif
