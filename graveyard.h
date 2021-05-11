#ifndef __GRAVEYARD_H__
#define __GRAVEYARD_H__

#include <string>
#include <vector>
#include <memory>

typedef std::vector<std::string> card_template_t;

class Component;

class Xwindow;

struct Graveyard_empty {
    std::string message;
};

class Graveyard{
    private:
    std::vector<std::shared_ptr<Component>> minions;
    public:
    Graveyard();
    void add(std::shared_ptr<Component> c);
    bool isEmpty() const;
    std::shared_ptr<Component> pop();
    void display(std::shared_ptr<Xwindow> g, int x, int y) const;
    //std::shared_ptr<Component> peek(int n);
    card_template_t print() const;
};

std::ostream& operator<<(std::ostream& os, const Component & h);

#endif
