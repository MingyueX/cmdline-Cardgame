#include "player.h"
#include "board.h"
#include "ascii_graphics.h"
#include "component.h"


Player::Player(std::string Name, int HP, int Mag, std::string deck_from, bool test):
    board{}, hp{HP}, mag{Mag}, name{Name}, hand{}, 
    deck{deck_from}, testing_mode{test} {
        if(testing_mode == false) {
            deck.shuffle();
        }
        try {
            draw();
            draw();
            draw();
            draw();
        } catch(Cannot_draw& e){}
    }
    
void Player::set_Board(std::shared_ptr<Board> b) {
    board = b;
}

void Player::draw() {
    try {
        std::shared_ptr<Card> c = deck.pop();
        try {
            hand.add(c);
        } catch (Hand_full &e) {
            deck.push_first(c);
            throw Cannot_draw{"cannot draw card: " + e.message};
        }
    } catch (Deck_empty &e) {
        throw Cannot_draw{"cannot draw card: " + e.message};
    } 
}

void Player::addHand(std::shared_ptr<Card> c) {
    hand.add(c);
}

void Player::discard(int n) {
    try {
        hand.pop(n);
    } catch(Hand_DNE& e) {
        throw Hand_DNE{"no card at the position. cannot discard."};
    }
}

card_template_t Player::print(playernum player_num) const {
    if (player_num == player2) {
        return display_player_card(2,name,hp,mag);
    }
    return display_player_card(1,name,hp,mag);
}

void Player::change_mag(int n ){
    mag += n;
}

void Player::change_hp(int n) {
    hp += n;
}

int Player::get_hp() const {
    return hp;
}

card_template_t Player::show_hand() const{ 
    return hand.print();
}

void Player::play(int n) {
    std::shared_ptr<Card> c = hand.pop(n);
    int cost = c->get_cost();
    int init_mag = mag;
    if (cost > mag) {
        if (testing_mode) {
            mag = 0;
        } else {
            hand.in_add(c, n);
            throw No_magic{"Does not have enough magic", mag, cost};
        }
    } else {
        mag = mag - cost;
    }
    try {
        board->play(c);
    } catch(Cannot_play& e) {
        mag = init_mag;
        hand.in_add(c,n);
        throw e;
    }
}

void Player::play(int n, playernum tgt_player, int m) {
    //need to check for conditions here.
    std::shared_ptr<Card> c = hand.pop(n);
    int cost = c->get_cost();
    int init_mag = mag;
    if (cost > mag) {
        if (testing_mode) {
            mag = 0;
        }else {
            hand.in_add(c, n);
            throw No_magic{"Does not have enough magic", mag, cost};
        }
    } else {
        mag = mag - cost;
    }
    try{
        board->play(c, tgt_player, m);
    } catch(Cannot_play& e) {
        mag = init_mag;
        hand.in_add(c,n);
        throw e;
    } catch(Minion_DNE& e) {
        mag = init_mag;
        hand.in_add(c,n);
        throw Cannot_play{e.message};
    }
}

void Player::use(int m) {
    int cost;
    try {
        cost = board->get_acti_cost(m);
    }
    catch(Minion_DNE& e) {
        throw Minion_DNE{"cannot use ability because no minion is there."};
    }
    int init_mag = mag;
    if (cost > mag) {
        if (testing_mode) {
            mag = 0;
        } else {
            throw No_magic{"no enough magic to use ability.", mag, cost};
        }
    } else {
        mag = mag - cost;
    }
    try {
        board->activate(m);
    } catch(Cannot_activate& e) {
        mag = init_mag;
        throw e;
    } catch(Minion_DNE& e) {
        mag = init_mag;
        throw e;
    } catch(No_act_p& e) {
        mag = init_mag;
        throw e;
    }
}

void Player::use(int m, playernum tgt_player, int n) {
    int cost;
    try {
        cost = board->get_acti_cost(m);
    } catch(Minion_DNE& e) {
        throw Minion_DNE{"cannot use ability because no minion is there."};
    }
    int init_mag = mag;
    if (cost > mag) {
        if (testing_mode) { 
            mag = 0;
        } else {
            throw No_magic{"no enough magic to use ability.", mag, cost};
        }
    } else {
        mag = mag - cost;
    }
    try {
        board->activate(m,tgt_player, n);
    } catch(Cannot_activate& e) {
        mag = init_mag;
        throw e;
    } catch(Minion_DNE& e) {
        mag = init_mag;
        throw e;
    } catch(No_act_p& e ){
        mag = init_mag;
        throw e;
    }
}

void Player::display(std::shared_ptr<Xwindow>  g, int x, int y) const {
    int blank = (150 - 6 * name.size()) / 2;
    g->fillRectangle(x, y, 150, 120, Xwindow::WebGray);
    g->drawString(x+blank, y+60, name, Xwindow::White);
    g->fillRectangle(x, y+120-23, 23, 23, Xwindow::White);
    g->drawString(x+5, y+120-10, std::to_string(hp), Xwindow::WebGray);
    g->fillRectangle(x+150-23, y+120-23, 23, 23, Xwindow::White);
    g->drawString(x+150-17, y+120-10, std::to_string(mag), Xwindow::WebGray);
}

void Player::displayHand(std::shared_ptr<Xwindow> g) const {
    hand.display(g);
}
