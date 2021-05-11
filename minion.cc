#include "minion.h"
#include "ascii_graphics.h"


Minion::Minion(std::string card_name, int magic_cost, std::string desc,
               int attack, int defence):
        Component{card_name, magic_cost, type_minion, desc},
        attack{attack}, defence{defence}, action_pt{0} {}

int Minion::get_attack() const{
       return attack;
}

int Minion::get_defence() const{
       return defence;
}

int Minion::get_act_pt() const{
       return action_pt;
}

void Minion::change_act_pt(int n){
       action_pt += n;
}

void Minion::set_act_pt(int n) {
       action_pt = n;
}

void Minion::change_atk(int n){
       attack += n;
}

void Minion::change_def(int n){
       defence += n;
}

card_template_t Minion::print() const{
       return display_minion_no_ability(card_name,magic_cost,attack,defence);
}

card_template_t Minion::print(int atk, int def, int activ_cost) const{
       return display_minion_no_ability(card_name,magic_cost,atk,def);
}

std::vector<card_template_t> Minion::get_inspect_list() const{
       std::vector<card_template_t> res{};
       res.emplace_back(print());
       return res;
}

void Minion::notify(Board * board, Event event, playernum current, int notified, playernum n_owner,  int tgt, playernum t_owner) {}

int Minion::get_acti_cost() const{
       return 0;
}

void Minion::activate(Board * board, playernum whoactivated, int me){
       throw Cannot_activate{"this minion does not have activation ability with no target. "};
}

void Minion::activate(Board * board, playernum whoactivated, int me, playernum tgt_player, int tgt){
       throw Cannot_activate {"this minion does not have activation ability with target. "};
}

void Minion::displayMinion(std::shared_ptr<Xwindow> GD, int x, int y, int atk, int def, int activ_cost) const{
    GD->fillRectangle(x, y, 150, 120, Xwindow::SteelBlue);
    GD->drawString(x+5, y+13, card_name, Xwindow::White);
    GD->fillRectangle(x+150-15, y, 15, 23, Xwindow::White);
    GD->drawString(x+150-11, y+13, std::to_string(magic_cost), Xwindow::SteelBlue);
    GD->fillRectangle(x, y+23, 150, 2, Xwindow::LightGray);
    GD->drawString(x+5, y+38, "Minion", Xwindow::White);
    GD->fillRectangle(x, y+46, 150, 2, Xwindow::LightGray);
    unsigned int count = 0;
    int delta = 0;
    if (get_acti_cost()) {
        GD->fillRectangle(x, y+50, 23, 23, Xwindow::White);
        GD->drawString(x+5, y+60, std::to_string(activ_cost), Xwindow::SteelBlue);
        int z = x+30;
        while (count < desc.size()) {
            GD->drawString(z, y+60 + delta, desc.substr(count, 20), Xwindow::White);
            delta += 13;
            count += 20;
        }
    } else {
        while (count < desc.size()) {
            GD->drawString(x+5, y+60 + delta, desc.substr(count, 23), Xwindow::White);
            delta += 13;
            count += 23;
        }
    }
    GD->fillRectangle(x, y+120-23, 23, 23, Xwindow::White);
    GD->drawString(x+5, y+120-10, std::to_string(atk), Xwindow::SteelBlue);
    GD->fillRectangle(x+150-23, y+120-23, 23, 23, Xwindow::White);
    GD->drawString(x+150-17, y+120-10, std::to_string(def), Xwindow::SteelBlue);
}

void Minion::display(std::shared_ptr<Xwindow> GD, int x, int y) const {
       displayMinion(GD,x,y,get_attack(),get_defence(),get_acti_cost());
}
