#ifndef __SPELLS_H__
#define __SPELLS_H__

#include "card.h"
#include "playernum.h"
class Board;

class GraphicsDisplay;

struct CannotCast{
    std::string msg;
};

class Spell : public Card {
    public:
    Spell(std::string card_name, 
          int magic_cost, std::string desc);
    card_template_t print() const override;
    void display(std::shared_ptr<Xwindow> GD, int x, int y) const override;
    virtual void cast(Board* b, playernum whoplayed);
    virtual void cast(Board* b, playernum whoplayed, playernum tgt_player, int n);
};

#endif
