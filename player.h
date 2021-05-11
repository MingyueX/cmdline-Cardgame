#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "hand.h"
#include "playernum.h"
#include "deck.h"

typedef std::vector<std::string> card_template_t;

class Board;

class GraphicsDisplay;

struct Cannot_draw{
    std::string msg;
};

struct No_magic {
    std::string message;
    int cur_mag;
    int need_mag;
};

class Player{
    std::shared_ptr<Board> board;
    int hp;
    int mag; //magic
    std::string name;
    Hand hand;
    Deck deck;
    bool testing_mode;
    public:
    Player(std::string Name, int HP, int Mag, std::string deck_from, bool test);
    void set_Board(std::shared_ptr<Board> board);
    void draw();
    void addHand(std::shared_ptr<Card> c);
    void discard(int n);
    card_template_t print(playernum player_num) const;
    void change_mag(int n);
    void change_hp(int n);
    int get_hp() const;
    card_template_t show_hand() const;
    void play(int c);
    void play(int c, playernum tgt_player, int n);
    void use(int m);
    void use(int m, playernum tgt_player, int n);
    void display(std::shared_ptr<Xwindow> g, int x, int y) const;
    void displayHand(std::shared_ptr<Xwindow> g) const;
};

#endif
