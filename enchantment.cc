#include "enchantment.h"
#include "minion.h"
#include "ascii_graphics.h"

Enchantment::Enchantment(std::string card_name, int magic_cost, std::string desc, std::string eff_atk, std::string eff_def):
        Component{card_name, magic_cost, type_enchantment, desc},
        next{},
        s{unbounded}, eff_atk{eff_atk}, eff_def{eff_def} {}

int Enchantment::get_attack() const{
        return next->get_attack();
}

int Enchantment::get_defence() const{
        return next->get_defence();
}

int Enchantment::get_act_pt() const{
        return next->get_act_pt();
}

card_template_t Enchantment::print() const{
        if (s == bounded){
                return next->print(get_attack(),get_defence(),get_acti_cost());
        }
        return display_enchantment(card_name,magic_cost,desc);
}

card_template_t Enchantment::print(int atk, int def, int activ_cost) const{
        return next->print(atk,def, activ_cost);
}

std::shared_ptr<Component> Enchantment::get_base() const{
        if (next->get_type() == type_minion){
                return next;
        }
        std::shared_ptr<Enchantment> m = std::dynamic_pointer_cast<Enchantment>(next);
        return m->get_base();
}

void Enchantment::change_act_pt(int n){
        next->change_act_pt(n);
}

void Enchantment::set_act_pt(int n){
        next->set_act_pt(n);
}

void Enchantment::change_atk(int n){
        next->change_atk(n);
}

void Enchantment::change_def(int n){
        next->change_def(n);
}

std::vector<card_template_t> Enchantment::get_inspect_list() const{
        std::vector<card_template_t> res = next->get_inspect_list();
        res.emplace_back(display_enchantment(card_name,magic_cost,desc));
        return res;
}

void Enchantment::set_next(std::shared_ptr<Component> next_c){
        next = next_c;
        s = bounded;
}

std::shared_ptr<Component> Enchantment::get_next() const{
        return next;
}

void Enchantment::notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) {
        next->notify(board, event, current, notified, n_owner, tgt, t_owner);
}

/*
void Enchantment::notify(Board * board, Event event, playernum current, int minion_idx){
        next->notify(board, event, current, minion_idx);
}
*/

int Enchantment::get_acti_cost() const{
        return next->get_acti_cost();
}

void Enchantment::activate(Board* board, playernum whoactivated, int me, playernum tgt_player, int tgt){
        next->activate(board,whoactivated,me,tgt_player,tgt);
}

void Enchantment::activate(Board* board, playernum whoactivated, int me){
        next->activate(board,whoactivated,me);
}

void Enchantment::display(std::shared_ptr<Xwindow> GD, int x, int y) const {
        if (s == bounded){
                //next->display(GD, x, y);
                displayMinion(GD,x,y,get_attack(),get_defence(),get_acti_cost());
                return;
        }
        GD->fillRectangle(x, y, 150, 120, Xwindow::CadetBlue);
        GD->drawString(x+5, y+13, card_name, Xwindow::White);
        GD->fillRectangle(x+150-15, y, 15, 23, Xwindow::White);
        GD->drawString(x+150-11, y+13, std::to_string(magic_cost), Xwindow::CadetBlue);
        GD->fillRectangle(x, y+23, 150, 2, Xwindow::LightGray);
        GD->drawString(x+5, y+38, "Enchantment", Xwindow::White);
        GD->fillRectangle(x, y+46, 150, 2, Xwindow::LightGray);
        unsigned int count = 0;
        int delta = 0;
        while (count < desc.size()) {
            GD->drawString(x+5, y+60 + delta, desc.substr(count, 23), Xwindow::White);
            delta += 13;
            count += 23;
        }
        if (eff_atk != "") {
        GD->fillRectangle(x, y+120-23, 23, 23, Xwindow::White);
        GD->drawString(x+5, y+120-10, eff_atk, Xwindow::CadetBlue);
        GD->fillRectangle(x+150-23, y+120-23, 23, 23, Xwindow::White);
        GD->drawString(x+150-17, y+120-10, eff_def, Xwindow::CadetBlue);
        }
}

void Enchantment::displayMinion(std::shared_ptr<Xwindow> GD, int x, int y, int atk, int def, int activ_cost) const{
        next->displayMinion(GD,x,y,atk,def,activ_cost);
}
