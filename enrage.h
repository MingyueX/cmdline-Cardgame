#ifndef __ENRAGE_H__
#define __ENRAGE_H__
#include "enchantment.h"


class Enrage : public Enchantment {
    private:
    int add_atk;
    public:
    Enrage();
    void set_next(std::shared_ptr<Component> next_c) override;
    int get_attack() const override;
    int get_defence() const override;
    card_template_t print() const override;
    std::vector<card_template_t> get_inspect_list() const override;
};

#endif
