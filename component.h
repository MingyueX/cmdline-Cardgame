#ifndef __COMPONENT_H__
#define __COMPONENT_H__
#include "card.h"
#include "event.h"
#include "playernum.h"

class Board;

struct Cannot_activate{
    std::string msg;
};

class Component : public Card {
    public:
    Component(std::string card_name, int magic_cost, card_type type, std::string desc);
    card_template_t inspect() const;
    virtual card_template_t print() const = 0;
    virtual card_template_t print(int atk, int def, int activ_cost) const = 0;
    virtual int get_attack() const = 0;
    virtual int get_defence() const = 0;
    virtual int get_act_pt() const = 0; 
    virtual int get_acti_cost() const = 0;

    virtual void change_act_pt(int n) = 0;
    virtual void set_act_pt(int n) = 0;
    virtual void change_atk(int n) = 0;
    virtual void change_def(int n)  = 0;
    void displayMinion(std::shared_ptr<Xwindow> GD, int x, int y) const;
    virtual void displayMinion(std::shared_ptr<Xwindow> GD, int x, int y, int atk, int def, int activ_cost) const = 0;
    virtual std::vector<card_template_t> get_inspect_list() const = 0;
    virtual void notify(Board * board, Event event, playernum current, int notified, playernum n_owner, int tgt, playernum t_owner) = 0;
    virtual void activate(Board * board, playernum whoactivated, int me) = 0;
    virtual void activate(Board * board, playernum whoactivated, int me, playernum tgt_player, int tgt) = 0;
};

#endif
