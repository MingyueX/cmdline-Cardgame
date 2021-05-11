#ifndef __DRBOOM_H__
#define __DRBOOM_H__
#include "minion.h"

class DrBoom : public Minion {
    int acti_cost;
    public:
    DrBoom();
    int get_acti_cost() const override;
    void activate(Board* b, playernum whoactivated, int me) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
};

#endif
