#include "spell.h"
#include "ascii_graphics.h"

Spell::Spell(std::string card_name, int magic_cost, 
             std::string desc):
    Card{card_name, magic_cost, type_spell, desc} {}

card_template_t Spell::print() const{
    return display_spell(card_name, magic_cost, desc);
}

void Spell::cast(Board* b, playernum whoplayed){
    throw CannotCast{"wrong argument for spell: need target"};}

void Spell::cast(Board* b, playernum whoplayed, playernum tgt_player, int n){
    throw CannotCast{"wrong argument for spell: this spell has no target"};}

void Spell::display(std::shared_ptr<Xwindow> GD, int x, int y) const {
    GD->fillRectangle(x, y, 150, 120, Xwindow::Orange);
    GD->drawString(x+5, y+13, card_name, Xwindow::White);
    GD->fillRectangle(x+150-15, y, 15, 23, Xwindow::White);
    GD->drawString(x+150-11, y+13, std::to_string(magic_cost), Xwindow::Orange);
    GD->fillRectangle(x, y+23, 150, 2, Xwindow::LightGray);
    GD->drawString(x+5, y+38, "Spell", Xwindow::White);
    GD->fillRectangle(x, y+46, 150, 2, Xwindow::LightGray);
    unsigned int count = 0;
    int delta = 0;
    while (count < desc.size()) {
        GD->drawString(x+5, y+60 + delta, desc.substr(count, 23), Xwindow::White);
        delta += 13;
        count += 23;
    }
}
