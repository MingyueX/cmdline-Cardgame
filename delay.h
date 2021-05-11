#ifndef __DELAY_H__
#define __DELAY_H__
#include "enchantment.h"


class Delay : public Enchantment {
    public:
    Delay();
    void set_act_pt(int n) override;
};

#endif
