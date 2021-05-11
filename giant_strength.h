#ifndef __GIANT_STRENGTH_H__
#define __GIANT_STRENGTH_H__
#include "enchantment.h"


class Giant_s : public Enchantment {
    public:
    Giant_s();
    int get_attack() const override;
    int get_defence() const override;
    card_template_t print() const override;
    std::vector<card_template_t> get_inspect_list() const override;
};

#endif
