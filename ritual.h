#ifndef __RITUAL_H__
#define __RITUAL_H__
#include "card.h"
#include "event.h"
#include "playernum.h"

class Board;

class Ritual : public Card {
    int charge;
    int acti_cost; //activation cost

    public:
    Ritual(std::string card_name, int magic_cost,
           std::string desc, int charge, int acti_cost);
    card_template_t print() const override;
    void display(std::shared_ptr<Xwindow> GD, int x, int y) const override;
    int get_acti_cost();
    int get_charge();
    void change_charge(int n);
    virtual void notify(Board * board, Event event, playernum current, playernum owner, int tgt, playernum t_owner) = 0;
};

#endif

