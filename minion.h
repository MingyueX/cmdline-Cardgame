#ifndef __MINION_H__
#define __MINION_H__
#include "component.h"

class Minion : public Component {
    protected:
    int attack;
    int defence;
    int action_pt;
    public:
    Minion(std::string card_name, int magic_cost, std::string desc,
           int attack, int defence);
    int get_act_pt() const override;
    int get_attack() const override;
    int get_defence() const override;
    virtual int get_acti_cost() const override;
    void display(std::shared_ptr<Xwindow> GD, int x, int y) const override;
    void displayMinion(std::shared_ptr<Xwindow> GD, int x, int y, int atk, int def, int activ_cost) const override;

    void change_act_pt(int n) override;
    void set_act_pt(int n) override;
    void change_atk(int n) override;
    void change_def(int n) override;
    card_template_t print() const override;
    card_template_t print(int atk, int def, int activ_cost) const override;
    std::vector<card_template_t> get_inspect_list() const override;
    void notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) override;
    void activate(Board * board, playernum whoactivated, int me) override;
    void activate(Board * board, playernum whoactivated, int me, playernum tgt_player, int tgt) override;
};

#endif
