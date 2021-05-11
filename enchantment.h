#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include "component.h"
#include <memory>

enum state : int{
    bounded = 0,
    unbounded = 1
};

class Enchantment : public Component {
    protected:
    std::shared_ptr<Component> next;
    state s;
    std::string eff_atk;
    std::string eff_def;
    public:
    Enchantment(std::string card_name, int magic_cost, std::string desc, std::string eff_atk = "", std::string eff_def = "");
    int get_attack() const override;
    int get_defence() const override;
    int get_act_pt() const override;
    int get_acti_cost() const override;

    void set_act_pt(int n) override;
    void change_act_pt(int n) override;
    void change_atk(int n) override;
    void change_def(int n) override;
    void display(std::shared_ptr<Xwindow> GD, int x, int y) const override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
    std::shared_ptr<Component> get_base() const;
    virtual void set_next(std::shared_ptr<Component> next_c);
    std::shared_ptr<Component> get_next() const;
    std::vector<card_template_t> get_inspect_list() const override;
    void notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) override;
//    void notify(Board * board, Event event, playernum current, int minion_idx) override;
    void activate(Board* board, playernum whoactivated, int me) override;
    void activate(Board* board, playernum whoactivated, int me, playernum tgt_player, int tgt) override;
    void displayMinion(std::shared_ptr<Xwindow> GD, int x, int y, int atk, int def, int activ_cost) const override;
};

#endif
