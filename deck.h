#ifndef __DECK_H__
#define __DECK_H__


#include <string>
#include <vector>
#include <memory>
#include "card.h"

//expection
struct Deck_empty {
    std::string message;
};


class Deck {
    std::string filename;
    std::vector<std::shared_ptr<Card>> deck;
    public:
    //ctor
    Deck(std::string filename);
    
    //read from file and form a deck
    void initDeck(std::string filename);
    // shuffle
    void shuffle();
    //check empty
    bool is_empty() const;
    void push_first(std::shared_ptr<Card> c);
    //pop card from deck
    std::shared_ptr<Card> pop();
    card_template_t print() const;
};


#endif 
