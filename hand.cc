#include "hand.h"
#include "card.h"
#include "ascii_graphics.h"

Hand::Hand():
    cards{}{}

void Hand::add(std::shared_ptr<Card> c){
    if (isFull()){
        throw Hand_full{"The hand is full"};
    }
    cards.emplace_back(c);
}

void Hand::in_add(std::shared_ptr<Card> c, int n) {
    cards.insert(cards.begin() + n - 1, c);
}

bool Hand::isFull(){
    return cards.size() == 5;
}

void Hand::display(std::shared_ptr<Xwindow> g) const{
    for (unsigned int i = 0; i < cards.size(); i++) {
        cards[i]->display(g, 20 + 160 * i, 660);
    }
}

std::shared_ptr<Card> Hand::peek(int n){
    if (n > cards.size()){
        throw Hand_DNE{"You don't have card at " + std::to_string(n), n};
    }
    return cards.at(n - 1);
}

std::shared_ptr<Card> Hand::pop(int n){
    std::shared_ptr<Card> res = peek(n);
    cards.erase(cards.begin() + n - 1);
    return res;
}

card_template_t Hand::print() const{
    card_template_t result{};
    for (auto c : cards){
        result = result + c->print();
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Hand & h){
    os << h.print();
    return os;
}
