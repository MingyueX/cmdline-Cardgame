#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

#include "deck.h"

#include "all_cards.h"

#include "ascii_graphics.h"

Deck::Deck(std::string filename):
    filename{filename} {
        initDeck(filename);
    }

void Deck::initDeck(std::string filename) {
    std::ifstream in{filename};
    if (in.is_open() ==  false) {
        std::cout << "The file is not exits or cannot open. Using default instead" << std::endl;
        initDeck("default.deck");
        return;
    }
    std::string card_name;
    int i = 0;
    while (std::getline(in, card_name)) {
        i++;
        if (card_name == "Banish") {
            deck.emplace_back(std::make_shared<Banish>());
        } else if (card_name == "Unsummon") {
            deck.emplace_back(std::make_shared<Unsummon>());
        } else if (card_name == "Recharge") {
            deck.emplace_back(std::make_shared<Recharge>());
        } else if (card_name == "Disenchant") {
            deck.emplace_back(std::make_shared<Disenchant>());
        } else if (card_name == "Raise Dead") {
            deck.emplace_back(std::make_shared<RaiseDead>());
        } else if (card_name == "Blizzard") {
            deck.emplace_back(std::make_shared<Blizzard>());
        } else if (card_name == "Dark Ritual") {
            deck.emplace_back(std::make_shared<Dark_R>());
        } else if (card_name == "Aura of Power") {
            deck.emplace_back(std::make_shared<Aura_O_P>());
        } else if (card_name == "Standstill") {
            deck.emplace_back(std::make_shared<Standstill>());
        } else if (card_name == "Giant Strength") {
            deck.emplace_back(std::make_shared<Giant_s>());
        } else if (card_name == "Enrage") {
            deck.emplace_back(std::make_shared<Enrage>());
        } else if (card_name == "Delay") {
            deck.emplace_back(std::make_shared<Delay>());
        } else if (card_name == "Magic Fatigue") {
            deck.emplace_back(std::make_shared<Magic_F>());
        } else if (card_name == "Silence") {
            deck.emplace_back(std::make_shared<Silence>());
        } else if (card_name == "Unsummon") {
            deck.emplace_back(std::make_shared<Unsummon>());
        } else if (card_name == "Air Elemental") {
            deck.emplace_back(std::make_shared<Air_ele>());
        } else if (card_name == "Earth Elemental") {
            deck.emplace_back(std::make_shared<Earth_ele>());
        } else if (card_name == "Bomb") {
            deck.emplace_back(std::make_shared<Bomb>());
        } else if (card_name == "Fire Elemental") {
            deck.emplace_back(std::make_shared<Fire_ele>());
        } else if (card_name == "Potion Seller") {
            deck.emplace_back(std::make_shared<Potion_S>());
        } else if (card_name == "Novice Pyromancer") {
            deck.emplace_back(std::make_shared<Novice_P>());
        } else if (card_name == "Apprentice Summoner") {
            deck.emplace_back(std::make_shared<Apprentice>());
        } else if (card_name == "Master Summoner") {
            deck.emplace_back(std::make_shared<Master_S>());
        } else if (card_name == "Dr Boom") {
            deck.emplace_back(std::make_shared<DrBoom>());
	} else if (card_name == "Coin") {
	    deck.emplace_back(std::make_shared<Coin>());
        } else {
            std::cout<<"Unknown card in your deck: "<<card_name<<std::endl;
            continue;
        }
    }
}

bool Deck::is_empty() const{
    return deck.empty();
}

std::shared_ptr<Card> Deck::pop() {
    if (!deck.empty()) {
        std::shared_ptr<Card> res = deck.at(0);
        deck.erase(deck.begin());
        return res;
    } else {
        throw Deck_empty{"The deck is empty"};
    }
}

void Deck::push_first(std::shared_ptr<Card> c) {
    deck.insert(deck.begin(), c);
}

void Deck::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng{seed};
    std::shuffle( deck.begin(), deck.end(), rng );
    return;
}

card_template_t Deck::print() const{
    if (is_empty()){
        return CARD_TEMPLATE_BORDER;
    }
    return deck.at(0)->print();
}
