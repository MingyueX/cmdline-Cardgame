#ifndef __APPRENTICE_H__
#define __APPRENTICE_H__
#include "minion.h"

class Apprentice : public Minion {
    int acti_cost;
    public:
    Apprentice();
    int get_acti_cost() const override;
    void activate(Board* board, playernum whoactivated, int me) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
};

#endif
