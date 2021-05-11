#ifndef __MAGIC_FATIGUE_H__
#define __MAGIC_FATIGUE_H__
#include "enchantment.h"


class Magic_F : public Enchantment {
    public:
    Magic_F();
    int get_acti_cost() const override;
};

#endif
