#ifndef __MASTER_SUMMONER_H__
#define __MASTER_SUMMONER_H__
#include "minion.h"

class Master_S : public Minion {
    int acti_cost;
    public:
    Master_S();
    int get_acti_cost() const override;
    void activate(Board* b, playernum whoactivated, int me) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
};

#endif
