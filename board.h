#ifndef __BOARD_H__
#define __BOARD_H__
#include "card.h"
#include <vector>
#include <map>
#include <memory>
#include <string>
#include "graveyard.h"
#include "playernum.h"
#include "event.h"
#include "window.h"

typedef std::vector<std::string> card_template_t;

class Player;

class Ritual;

class Component;

class Graveyard;

playernum other(playernum current);

//expection
struct Minion_DNE {
    std::string message;
    playernum player;
    int n;
    //Minion_DNE(std::string message, playernum p, int n);
};

struct Ritual_DNE{
    std::string message;
    playernum p;
};

struct No_act_p {
    std::string message;
    playernum p;
    int n;
    //No_act_p(std::string message, std::shared_ptr<Card> c);
};

struct Cannot_play{
    std::string msg;
};

struct No_enchantment{
    std::string msg;
};

struct No_space{
    std::string msg;
};

enum Game_state : int {
    no_winner = 0,
    p1_win = 1,
    p2_win = 2
};

struct Minion_Pos{
    playernum player;
    int position;
};

class Board{
    private:
    std::shared_ptr<Xwindow> GD;
    playernum current_player;
    Game_state s;
    std::map<playernum, std::shared_ptr<Player>> players;
    std::map<playernum, std::vector<std::shared_ptr<Component>>> minions;
    std::map<playernum, std::shared_ptr<Ritual>> ritual;
    std::map<playernum, Graveyard> graveyards;
    void cleanup_d();
    bool is_dead(std::shared_ptr<Component> m, const std::vector<std::shared_ptr<Component>> dead) const;
    bool cleanup_insession;
    bool cleanup_needed;
    void destroy_all_delay();
    std::shared_ptr<Component> destroy_delays(std::shared_ptr<Component>);
    std::shared_ptr<Component> get_base(std::shared_ptr<Component>) const;
    Minion_Pos find_minion(std::shared_ptr<Component> base);
    void cleanup();
    void notifyAll(Event event, int tgt, playernum t_owner);
    public:
    Board(playernum current, std::map<playernum, std::shared_ptr<Player>> players);
    void enableGDisplay();
    void display() ;
    void graphics_setup() ;
    void graphics_clearboard() ;
    void play(std::shared_ptr<Card> c, playernum tgt_player, int n);
    void play(std::shared_ptr<Card> c);
    void activate(int m);
    void activate(int m, playernum tgt_player, int n);
    void attack(int n);
    void attack(int n, int m);
    bool checkAvailable(playernum p, int n) const;
    int getMinion_atk(playernum player, int n);
    int get_acti_cost(int m) const;
    void addMag(playernum player, int n);
    void kill(playernum player, int n);
    void endTurn();
    void startTurn();
    void change_hp(int n, playernum tgt_player);//aoe
    void change_all_hp(int n);
    void change_atk_hp(int atk, int def, playernum tgt_player, int m);
    void change_charge(playernum player, int n);
    void send_back(playernum player, int n);
    void pop_graveyards(playernum player);
    void remove_outer(playernum player, int n);
    void add_minion(playernum side, std::shared_ptr<Component> m);
    Game_state who_win();
    card_template_t print() const;
    card_template_t inspect(int i) const;
};

std::ostream& operator<<(std::ostream& os, const Board & b);

#endif
