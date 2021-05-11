#include "all_cards.h"
#include "board.h"
#include "player.h"
#include "ritual.h"
#include "component.h"
#include "graveyard.h"
#include "ascii_graphics.h"
#include <algorithm>
#include <iostream>


void Board::enableGDisplay() {
    std::shared_ptr<Xwindow> xw = std::make_shared<Xwindow>();
    GD = xw;
    graphics_setup();
}

Board::Board(playernum current, std::map<playernum, std::shared_ptr<Player>> players): 
    GD{nullptr}, current_player{current}, players{players}, cleanup_insession{false}, cleanup_needed{false}{
        s = no_winner;
        minions.emplace(player1,std::vector<std::shared_ptr<Component>>());
        minions.emplace(player2,std::vector<std::shared_ptr<Component>>());
        graveyards.emplace(player1,Graveyard());
        graveyards.emplace(player2,Graveyard());
        ritual.emplace(player1,std::shared_ptr<Ritual>(nullptr));
        ritual.emplace(player2,std::shared_ptr<Ritual>(nullptr));
    }

void Board::display() {
    if (GD == nullptr) {
        return;
    }
    graphics_clearboard();

    for (size_t i = 0; i < minions.at(current_player).size(); i++) {
        auto m = minions.at(current_player)[i];
        int x = 20 + 160 * i;
        int y = 390;
        m->display(GD, x, y);
    }
    for (size_t i = 0; i < minions.at(other(current_player)).size(); i++) {
        auto m = minions.at(other(current_player))[i];
        int x = 20 + 160 * i;
        int y = 150;
        m->display(GD, x, y);
    }
    graveyards.at(current_player).display(GD, 660, 520);
    graveyards.at(other(current_player)).display(GD, 20, 20);
    if (ritual.at(current_player)) {
        ritual.at(current_player)->display(GD, 20, 520);
    }
    if (ritual.at(other(current_player))) {
        ritual.at(other(current_player))->display(GD, 660, 20);
    }
    players.at(current_player)->display(GD, 340, 520);
    players.at(other(current_player))->display(GD, 340, 20);
    players.at(current_player)->displayHand(GD);
}

card_template_t Board::print() const {
    playernum p1 = other(current_player);
    playernum p2 = current_player;
    card_template_t p1_player{};
    card_template_t p2_player{};
    card_template_t p1_minion{};
    card_template_t p2_minion{};
    p1_player = graveyards.at(p1).print() + CARD_TEMPLATE_EMPTY + players.at(p1)->print(p1) + CARD_TEMPLATE_EMPTY;
    if (ritual.at(p1) != std::shared_ptr<Ritual>(nullptr)) {
        p1_player = p1_player + ritual.at(p1)->print();
    } else {
        p1_player = p1_player + CARD_TEMPLATE_BORDER;
    }
    if (ritual.at(p2) != std::shared_ptr<Ritual>(nullptr)) {
        p2_player = ritual.at(p2)->print();
    } else {
        p2_player = CARD_TEMPLATE_BORDER;
    }
    p2_player = p2_player + CARD_TEMPLATE_EMPTY + players.at(p2)->print(p2) + CARD_TEMPLATE_EMPTY + graveyards.at(p2).print();
    for (unsigned int i = 0; i < 5; i++) {
        if (minions.at(p1).size() > i) {
            p1_minion = p1_minion + minions.at(p1).at(i)->print();
        } else {
            p1_minion = p1_minion + CARD_TEMPLATE_BORDER;
        }
        if (minions.at(p2).size() > i){
            p2_minion = p2_minion + minions.at(p2).at(i)->print();
        } else {
            p2_minion = p2_minion + CARD_TEMPLATE_BORDER;
        }
    }
    card_template_t upper = add_left_right_border(append(p1_player,p1_minion));
    card_template_t lower = add_left_right_border(append(p2_minion,p2_player));
    return add_top_bottom_border(append(append(upper, CENTRE_GRAPHIC),lower));
}

std::ostream& operator<<(std::ostream& os, const Board & b){
    os << b.print();
    return os;
}

playernum other(playernum player) {
    if (player == player1) {
        return player2;
    } else {
        return player1;
    }
}

bool Board::is_dead(std::shared_ptr<Component> m, const std::vector<std::shared_ptr<Component>> dead) const{
    m = get_base(m);
    for (auto d : dead){
        if (d == m){
            return true;
        }
    }
    return false;
}
std::shared_ptr<Component> Board::get_base(std::shared_ptr<Component> mi) const{
    if (mi->get_type() == type_minion){
        return mi;
    }
    return std::dynamic_pointer_cast<Enchantment>(mi)->get_base();
}

Minion_Pos Board::find_minion(std::shared_ptr<Component> base){
    for (unsigned int i = 0; i < minions.at(current_player).size(); i++){
        if (get_base(minions.at(current_player).at(i)) == base){
            return Minion_Pos{current_player, static_cast<int> (i+1)};
        }
    }
    for (int i = 0; i < minions.at(other(current_player)).size(); i++){
        if (get_base(minions.at(other(current_player)).at(i)) == base){
            return Minion_Pos{other(current_player), i+1};
        }
    }
    throw Minion_DNE{"minion you're trying to find does not exist on board", current_player,0};
}

void Board::cleanup() {
    if (cleanup_insession) {
        cleanup_needed = true;
        return;
    }
    cleanup_insession = true;
    cleanup_needed = false;
    std::vector<std::shared_ptr<Component>> dead_minions{};
    for (size_t i = 0; i < minions.at(current_player).size(); i ++){
        std::shared_ptr<Component> dec_minion = minions.at(current_player).at(i);
        if (dec_minion->get_defence() <= 0){
            if (!is_dead(dec_minion, dead_minions)){
                dead_minions.push_back(get_base(dec_minion));
            }
        }
    }
    for (size_t i = 0; i < minions.at(other(current_player)).size(); i ++){
        std::shared_ptr<Component> dec_minion = minions.at(other(current_player)).at(i);
        if (dec_minion->get_defence() <= 0){
            if (!is_dead(dec_minion, dead_minions)){
                dead_minions.push_back(get_base(dec_minion));
            }
        }
    }
    for (auto m : dead_minions){
        Minion_Pos pos;
        try{
            pos = find_minion(m);
        } catch(Minion_DNE& e){
            continue;
        }
        notifyAll(min_out, pos.position, pos.player);
    }
    
    while (dead_minions.size() > 0){
        Minion_Pos dead_m;
        try{
            dead_m = find_minion(dead_minions.at(0));
        }catch(Minion_DNE& e){
            dead_minions.erase(dead_minions.begin());
            continue;
        }
        dead_minions.erase(dead_minions.begin());
        std::shared_ptr<Component>& m = minions.at(dead_m.player).at(dead_m.position - 1);
        graveyards.at(dead_m.player).add(m);
        minions.at(dead_m.player).erase(minions.at(dead_m.player).begin() + dead_m.position - 1);
    }

    if (players.at(player1)->get_hp() <= 0) {
        s = p2_win;
    }
    if (players.at(player2)->get_hp() <= 0){
        s = p1_win;
    }
    cleanup_insession = false;
    if (cleanup_needed){
        cleanup();
    }
    return;
}

Game_state Board::who_win() {
    return s;
}

bool Board::checkAvailable(playernum p, int n) const{
    unsigned int m = n;
    if (m < 1 || minions.find(p)->second.size() < m) {
        return false;
    } else {
        return true;
    }
}

void Board::attack(int n) {
    if (!checkAvailable(current_player, n)) {
        std::string m = "No minion at " + std::to_string(n) + " on your side";
        throw Minion_DNE{m, current_player, n};
    }

    auto m = minions.at(current_player)[n - 1];
    if (m->get_act_pt() > 0) {
        players.at(other(current_player))->change_hp(- m->get_attack());
        m->change_act_pt(-1);
        cleanup();
        return;
    } else {
        std::string message = "This minion does not have action point";
        throw No_act_p{message, current_player, n};
    }
}

void Board::attack(int n, int m) {
    if (!checkAvailable(current_player,n)) {
        std::string attack_m1 = "No minion at " + std::to_string(n) + " on your side";
        throw Minion_DNE{attack_m1, current_player, n};
    }
    if (!checkAvailable(other(current_player),m)) {
        std::string attack_m2 = "No minion at " + std::to_string(m) + "  on enemy side";
        throw Minion_DNE{attack_m2, other(current_player), m};
    }
        
    auto ally = minions.at(current_player)[n - 1];
    auto enemy = minions.at(other(current_player))[m - 1];
    if (ally->get_act_pt() > 0) {
        ally->change_def(- enemy->get_attack());
        enemy->change_def(- ally->get_attack());
        ally->change_act_pt(-1);
        cleanup();
        return;
    } else {
        std::string message = "This minion does not have action point";
        throw No_act_p{message, current_player, n};
    }
}

void Board::play(std::shared_ptr<Card> c) {
    if (c->get_type() == type_ritual) {
        ritual.at(current_player) = std::dynamic_pointer_cast<Ritual>(c);
        return;
    }
    if (c->get_type() == type_minion) {
        if (minions.at(current_player).size() < 5) { 
            minions.at(current_player).push_back(std::dynamic_pointer_cast<Component>(c));
            int num_minions = minions.at(current_player).size();
            notifyAll(min_in, num_minions, current_player);
            return;
        } 
        throw Cannot_play{"no enough space to play minion"};
    }
    if (c->get_type() == type_spell) {
        try {
            std::dynamic_pointer_cast<Spell>(c)->cast(this, current_player);
        } catch(CannotCast & e) {
            throw Cannot_play{e.msg};
        }
        return;
    }
    throw Cannot_play{"enchantment has target"};
}

void Board::play(std::shared_ptr<Card> c, playernum tgt_player, int n) {
    if (c->get_type() == type_enchantment) {
        if (!(checkAvailable(tgt_player, n))) {
            std::string m = "No minion at " + std::to_string(n) + " on " + std::to_string(tgt_player) + "\'s side";
            throw Minion_DNE{m, tgt_player, n};
        }
        std::shared_ptr<Enchantment> e = std::dynamic_pointer_cast<Enchantment>(c);
        e->set_next(minions.at(tgt_player).at(n - 1));
        minions.at(tgt_player).at(n - 1) = std::dynamic_pointer_cast<Component>(e);
        cleanup();
        return;
    }
    if (c->get_type() == type_spell) {
        try{
        std::dynamic_pointer_cast<Spell>(c)->cast(this,current_player,tgt_player,n);
        } catch(CannotCast & e) {
            throw Cannot_play{e.msg};
        }
        return;
    }
    throw Cannot_play{"this card has no target"};
}

void Board::endTurn() {
    notifyAll(turn_end, 0, current_player);
    current_player = other(current_player);
    if (current_player == player1) {
        for (auto &p : players) {
            p.second->change_mag(1);
        }
    }
    startTurn();
    return;
}

void Board::startTurn(){
    try {
        players.at(current_player)->draw();
    } catch (Cannot_draw &e) {}
    for (auto c : minions.at(current_player)) {
        c->set_act_pt(1);
    }
    destroy_all_delay();
    notifyAll(turn_start, 0, current_player);
    return;
}

void Board::destroy_all_delay(){
    for (size_t i = 0; i < minions.at(current_player).size(); i++){
        minions.at(current_player).at(i) = destroy_delays(minions.at(current_player).at(i));
    }
}

std::shared_ptr<Component> Board::destroy_delays(std::shared_ptr<Component> m){
    if (m->get_type() == type_minion) return m;
    std::shared_ptr<Enchantment> enc = std::dynamic_pointer_cast<Enchantment>(m);
    if (enc->get_name() == "Delay"){
        return destroy_delays(enc->get_next());
    }
    enc->set_next(destroy_delays(enc->get_next()));
    return std::dynamic_pointer_cast<Component>(enc);
}

card_template_t Board::inspect(int i) const {
    if (checkAvailable(current_player, i)) {
        return minions.at(current_player).at(i - 1)->inspect();
    } else {
        std::string m = "No minion at " + std::to_string(i) + " on your side";
        throw Minion_DNE{m, current_player, i};
    }
}

void Board::change_hp(int n, playernum tgt_player) {
    for (auto m : minions.at(tgt_player)) {
        m->change_def(n);
    }
    cleanup();
    return;
}

void Board::change_all_hp(int n){
    for (auto m : minions.at(current_player)){
        m->change_def(n);
    }
    for (auto m : minions.at(other(current_player))){
        m->change_def(n);
    }
    cleanup();
    return;
}

void Board::change_atk_hp(int atk, int def, playernum tgt_player, int m) {
    if (checkAvailable(tgt_player, m)) {
        minions.at(tgt_player).at(m - 1)->change_atk(atk);
        minions.at(tgt_player).at(m - 1)->change_def(def);
        cleanup();
        return;
    } else {
        std::string msg = "No minion at " + std::to_string(m) + " on your side";
        throw Minion_DNE{msg, current_player, m};
    }
}

void Board::notifyAll(Event event, int tgt, playernum t_owner) {
    for (auto &m : minions) {
        size_t i = 0;
        while(i < m.second.size()) {
            m.second[i]->notify(this, event, current_player, i, m.first, tgt, t_owner);
            i++;
        }
        if(ritual.at(m.first)){
            ritual.at(m.first)->notify(this, event, current_player, m.first, tgt, t_owner);
        }
    }
}


int Board::getMinion_atk(playernum player, int n) {
    return minions.at(player)[n-1]->get_attack();
}

void Board::addMag(playernum player, int n) {
    players.at(player)->change_mag(n);
}

void Board::kill(playernum player, int n) {
    if (n == 0){
        if(!(ritual.at(player))){
            throw Ritual_DNE{"cannot kill ritual", player};
        }
        ritual.at(player) = std::shared_ptr<Ritual>{nullptr};
        return;
    }
    if (checkAvailable(player, n)) {
        graveyards.at(player).add(minions.at(player).at(n-1));
        minions.at(player).erase(minions.at(player).begin() + (n-1));
        notifyAll(min_out, n, player);
        return;
    }
    throw Minion_DNE{"cannot kill minion", player, n};
}

void Board::change_charge(playernum player, int n) {
    if(ritual.at(player)) {
        ritual.at(player)->change_charge(n);
        return;
    }
    throw Ritual_DNE{"cannot change charge", player};
}

void Board::send_back(playernum player, int n) {
    if (checkAvailable(player, n)) {
        std::shared_ptr<Component> c = minions.at(player).at(n - 1);
        if (c->get_type() == type_minion) {
            try {
                players.at(player)->addHand(std::dynamic_pointer_cast<Card> (c));
            } catch(Hand_full& e) {
                return;
            }
        } else {
            try {
                players.at(player)->addHand(std::dynamic_pointer_cast<Card>(std::dynamic_pointer_cast<Enchantment>(c)->get_base()));
            } catch(Hand_full& e) {
                return;
            }
        }
        minions.at(player).erase(minions.at(player).begin() + n - 1);
        return;
    }
    throw Minion_DNE{"no minion at position. cannot send back.", player, n};
}

void Board::pop_graveyards(playernum player) {
    std::shared_ptr<Component> c = graveyards.at(player).pop();
    if (minions.at(player).size() < 5) {
        int d = c->get_defence();
        c->change_def(1-d);
        minions.at(player).push_back(c);
        int num_minions = minions.at(player).size();
        notifyAll(min_in, num_minions, player);
        return;
    } else { 
        graveyards.at(player).add(c);
        throw No_space{"no enough space to play revived minion"};
    }
}

int Board::get_acti_cost(int m) const {
    if(!checkAvailable(current_player,m)) {
        throw Minion_DNE{"cannot get activation cost"};
    }
    return minions.at(current_player).at(m - 1)->get_acti_cost();
}

void Board::activate(int m) {
    if (!checkAvailable(current_player, m)) {
        throw Minion_DNE{"cannot activate because no minion is here"};
    }
    try {
        minions.at(current_player).at(m - 1)->activate(this, current_player, m);
    } catch(Cannot_activate& e) {
        throw e;
    }
}

void Board::activate(int m, playernum tgt_player, int n) {
    if (!checkAvailable(current_player, m)) {
        throw Minion_DNE{"cannot activate because no minion is here"};
    }
    try {
        minions.at(current_player).at(m - 1)->activate(this, current_player, m, tgt_player, n);
    } catch(Cannot_activate& e) {
        throw e;
    }
}

void Board::remove_outer(playernum player, int n) {
    if (!checkAvailable(player, n)) {
        throw Minion_DNE{"no minion to remove enchantment"};
    }
    std::shared_ptr<Component>& c = minions.at(player).at(n - 1);
    if (c->get_type() == type_minion) {
        throw No_enchantment{"The minion has no enchantment."};
    }
    c = std::dynamic_pointer_cast<Enchantment>(c)->get_next();
    cleanup();
}

void Board::add_minion(playernum side, std::shared_ptr<Component> m) {
    if (checkAvailable(side, 5)) {
        throw No_space{"board is full, cannot add minon. "};
    }
    minions.at(side).push_back(m);
    notifyAll(min_in, int(minions.at(side).size()), side);
}

void Board::graphics_setup() {
    if (GD == nullptr) {
        return;
    }
    GD->fillRectangle(0, 0, 830, 780, Xwindow::LightGray);
    GD->fillRectangle(10, 10, 810, 640, Xwindow::LSGray);
    graphics_clearboard();
    GD->drawTitle(340, 340, "SORCERY", Xwindow::WebGray);
    GD->drawTitle(345, 340, "SORCERY");
}

void Board::graphics_clearboard() {
    if (GD == nullptr) {
        return;
    }
    for (int i = 20; i <= 520; i += 500) {
        for (int j = 20; j <= 830 - 160; j += 320) {
            GD->fillRectangle(j, i, 150, 120, Xwindow::LightGray);
	    }
    }
    for (int i = 150; i <= 390; i += 240) {
	    for (int j = 20; j <= 830 - 160; j += 160) {
		    GD->fillRectangle(j, i, 150, 120, Xwindow::White);
	    }
    }
	for (int i = 20; i <= 830-160; i += 160) {
	    GD->fillRectangle(i, 660, 150, 120, Xwindow::White);
	}
}
