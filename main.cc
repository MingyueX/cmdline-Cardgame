#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "card.h"
#include "player.h"
#include "board.h"
#include "component.h"
#include "deck.h"
#include "ascii_graphics.h"
#include "deck.h"
#include "window.h"

#include "inp.h"

const std::string file_message = "The file provide cannot read or does not exit: ";

bool arg_testing(int len, const std::vector<std::string>& argv) noexcept;

bool arg_use_file(int len, const std::vector<std::string> & argv) noexcept;

bool arg_use_graphic(int len, const std::vector<std::string> & argv) noexcept;

std::string arg_filename(int len, const std::vector<std::string> & argv);

std::string arg_deck(int len, const std::vector<std::string>& argv, const std::string& kw, const std::string& default_deck = "default.deck");

void print_help_msg() noexcept;

int main(int argc, char *argv[]) {
    std::string p1name;
    std::string p2name;
    std::vector<std::string> args;
    for (int i = 0; i < argc; i ++){
        args.push_back(argv[i]);
    }
    std::string deck1 = arg_deck(argc, args, "-deck1");
    std::string deck2 = arg_deck(argc, args, "-deck2");

    bool testing = arg_testing(argc,args); // check -testing
    bool using_file = arg_use_file(argc,args); // check -init
    bool enable_graphic = arg_use_graphic(argc,args);
    std::string filename = "";

    if (using_file){
        filename = arg_filename(argc,args);
    }
    Inp in{using_file,filename};
    if (using_file && (! in.use_file())){
        std::cout << file_message << filename << std::endl;
    }

    if (! in.use_file()){
        std::cout<<"Player1 name: "<<std::endl;
    }
    in.getline(p1name);
    if (! in.use_file()){
        std::cout<<"Player2 name: "<<std::endl;
    }
    in.getline(p2name);

    //setup
    std::map<playernum, std::shared_ptr<Player>> players;
    players.emplace(player1, std::make_shared<Player>(p1name,20,3,deck1,testing));
    players.emplace(player2, std::make_shared<Player>(p2name,20,3,deck2,testing));
    playernum current = player1; // current player. 
    std::shared_ptr<Board> board = std::make_shared<Board> (current, players);
    players.at(player1)->set_Board(board);
    players.at(player2)->set_Board(board);
    if (enable_graphic) {
        board->enableGDisplay();
    }
    board->startTurn();

    std::string command;
    while (true){
        board->display();
        if (!((board->who_win() == no_winner) && in.getline(command))){
            break;
        }
        std::stringstream s{command};
        std::string cmd;
        s >> cmd;

        if((cmd == "draw") && testing){
            try {
                players.at(current)->draw();
            } catch (Cannot_draw &e) {
                std::cout << e.msg << std::endl;
            }
            continue;
        }
        if((cmd == "discard") && testing){
            int i;
            if (! (s >> i)){
                std::cout << "enter \"discard (int)\" to indicate which card you want to discard. "<<std::endl;
                continue;
            }
            try {
                players.at(current)->discard(i);
            }catch (Hand_DNE &e) {
                std::cout << e.message << std::endl;
            }
            continue;
        }
        if(cmd == "help"){
            print_help_msg();
            continue;
        }
        if(cmd == "hand"){
            std::cout<<players.at(current)->show_hand();
            continue;
        }
        if(cmd == "end"){
            current = other(current);
            board->endTurn();
            continue;
        }
        if(cmd == "board"){
            std::cout << board->print();
            continue;
        }
        if(cmd == "quit"){
            break;
        }
        if(cmd == "play"){
            int card_idx, tgtplayer;
            char tgt;
            if (!(s >> card_idx)){
                std::cout<<"enter \"play (int)\" to indicate which card to use."<<std::endl;
                continue;
            }
            if (!(s >> tgtplayer)){
                try{
                    players.at(current)->play(card_idx);
                } catch(Cannot_play& e) {
                    std::cout << e.msg << std::endl;
                } catch(No_magic &e) {
                    std::cout << "You do not have enough magic to play this card. " << std::endl;
                } catch (Hand_DNE &e) {
                    std::cout << e.message << std::endl;
                }
                continue;
            }
            playernum tgt_p{};
            if (tgtplayer == 1) {
                tgt_p = player1;
            }
            else if (tgtplayer == 2) {
                tgt_p = player2;
            } else {
                std::cout<<"target player must be 1 or 2"<<std::endl;
                continue;
            }

            if (!(s >> tgt)){
                std::cout<<"enter one more int/\"r\" to indicate your target"<<std::endl;
                continue;
            }
            if (isdigit(tgt) && ('1' <= tgt) && (tgt <= '5')){
                try{
                    players.at(current)->play(card_idx,tgt_p,tgt - '0');
                } catch(Cannot_play& e) {
                    std::cout << e.msg << std::endl;
                } catch (No_magic &e) {
                    std::cout << "You do not have enough magic to play this card. " << std::endl;
                } catch (Hand_DNE &e) {
                    std::cout << e.message <<std::endl;
                }
                continue;
            }
            if (tgt == 'r') {
                try{
                    players.at(current)->play(card_idx,tgt_p,0);
                }catch(Cannot_play& e){
                    std::cout << e.msg << std::endl;
                } catch (No_magic &e) {
                    std::cout << "You do not have enough magic to play this card. " << std::endl;
                } catch (Hand_DNE &e) {
                    std::cout << e.message <<std::endl;
                }
                continue;
            } else {
                std::cout<<"use an int or \"r\" to indicate the target minion/ritual. "<<std::endl;
                continue;
            }
        }

        
        if(cmd == "use"){
            int minion_idx, tgtplayer;
            char tgt;
            if (!(s >> minion_idx)){
                std::cout<<"enter \"use (int)\" to indicate which minion to use."<<std::endl;
                continue;
            }
            if (!(s >> tgtplayer)){
                try{
                    players.at(current)->use(minion_idx);
                } catch (No_magic &e) {
                    std::cout << "You do not have enough magic to use this minion. " << std::endl;
                } catch (Minion_DNE &e) {
                    std::cout << "Target does not exist. " << std::endl;
                } catch (Cannot_activate &e){
                    std::cout << e.msg << std::endl;
                } catch (No_act_p & e){
                    std::cout << "Minion has no action point left" << std::endl;
                }
                continue;
            }
            playernum tgt_p{};
            if (tgtplayer == 1) {
                tgt_p = player1;
            }
            else if (tgtplayer == 2) {
                tgt_p = player2;
            } else {
                std::cout<<"target player must be 1 or 2"<<std::endl;
                continue;
            }

            if (!(s >> tgt)){
                std::cout<<"enter one more int/\"r\" to indicate your target"<<std::endl;
                continue;
            }
            if (isdigit(tgt) && ('1' <= tgt) && (tgt <= '5')){
                try{
                    players.at(current)->use(minion_idx,tgt_p,tgt - '0');
                } catch(Cannot_activate& e) {
                    std::cout << e.msg << std::endl;
                } catch (No_magic &e) {
                    std::cout << "You do not have enough magic to use this minion. " << std::endl;
                } catch (Minion_DNE &e) {
                    std::cout << "Target does not exist. " <<std::endl;
                } catch (No_act_p & e){
                    std::cout << "Minion has no acion point left" << std::endl;
                }
                continue;
            }
            if (tgt == 'r') {
                try{
                    players.at(current)->use(minion_idx,tgt_p,0);
                }catch(Cannot_activate& e){
                    std::cout << e.msg << std::endl;
                }catch(No_act_p& e){
                    std::cout << "Minion has no action point left" << std::endl;
                }
                continue;
            } else {
                std::cout<<"use an int or \"r\" to indicate the target minion/ritual. "<<std::endl;
                continue;
            }
        }

        if(cmd == "attack"){
            int ally, enemy;
            if (!(s >> ally)) {
                std::cout << "use attack (int) to indicate which minion you want to attack with."<<std::endl;
                continue;
            }
            if (!(s >> enemy)){
                try 
                {
                    board->attack(ally);
                } catch (Minion_DNE &e) {
                    if (e.player == current){
                        std::cout << "You don't have minion at position " << e.n<<"."<<std::endl;
                    }
                    else{
                        std::cout << "Your enemy doesn't have minion at position " << e.n << "." << std::endl;
                    }
                } catch (No_act_p &e) {
                    std::cout << "Your minion does not have action point left. "<<std::endl;
                }
                continue;
            } 
            try {
                board->attack(ally, enemy);
            }
            catch (Minion_DNE &e) {
                if (e.player == current){
                    std::cout << "You don't have minion at position " << e.n<<"."<<std::endl;
                }
                else{
                    std::cout << "Your enemy doesn't have minion at position " << e.n << "." << std::endl;
                }
            }
            catch (No_act_p &e) {
                std::cout << "Your minion does not have action point left. " << std::endl;
            }
            continue;
        }

        if(cmd == "inspect"){
            int minion_idx;
            if (!(s >> minion_idx)) {
                std::cout << "use \"inspect (int)\" to indicate which minion you want to inspect. "<<std::endl;
            } else {
                try {
                    std::cout << board->inspect(minion_idx);
                } catch (Minion_DNE &e) {
                    std::cout << e.message << std::endl;
                }
            }
            continue;
        }
        std::cout << "your command is not valid. please consider the following: " << std::endl;
        print_help_msg();
    }
    if (board->who_win() != no_winner) {
        if (board->who_win() == p1_win) {
            std::cout << p1name << " win!" << std::endl; 
        } else {
            std::cout << p2name << " win!" << std::endl;
        }
    }
    players.at(player1)->set_Board(std::shared_ptr<Board>(nullptr));
    players.at(player2)->set_Board(std::shared_ptr<Board>(nullptr));
}



bool arg_testing(int len, const std::vector<std::string>& argv) noexcept{
    for (auto a : argv){
        if (a == "-testing"){
            return true;
        }
    }
    return false;
}

bool arg_use_file(int len, const std::vector<std::string> & argv) noexcept{
    for (auto a : argv){
        if (a == "-init"){
            return true;
        }
    }
    return false;
}

bool arg_use_graphic(int len, const std::vector<std::string> & argv) noexcept{
    for (auto a : argv){
        if (a == "-graphics"){
            return true;
        }
    }
    return false;
}

std::string arg_filename(int len, const std::vector<std::string> & argv){
    for (int i = 0; i < len - 1; i++) {
        if (argv.at(i) == "-init") {
            return argv.at(i + 1);
        }
    }
    return "";
}

std::string arg_deck(int len, const std::vector<std::string>& argv, const std::string& kw, const std::string& default_deck){
    for (int i = 0; i < len - 1; i++){
        if (argv.at(i) == kw){
            return argv.at(i + 1);
        }
    }
    return default_deck;
}

void print_help_msg() noexcept{
    std::cout << "Commands: " << "help -- Display this message." << std::endl;
    std::cout << std::setw(10) <<"" << "end -- End the current player's turn." << std::endl;
    std::cout << std::setw(10) <<"" << "quit -- End the game." << std::endl;
    std::cout << std::setw(10) <<"" << "attack minion other-minion -- Orders minion to attack other-minion." << std::endl;
    std::cout << std::setw(10) <<"" << "attack minion -- Orders minion to attack the opponent." << std::endl;
    std::cout << std::setw(10) <<"" << "play card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player." << std::endl;
    std::cout << std::setw(10) <<"" << "use minion [target-player target-card] -- Use minion’s special ability, optionally targeting target-card owned by target-player." << std::endl;
    std::cout << std::setw(10) <<"" << "inspect minion -- View a minion’s card and all enchantments on that minion." << std::endl;
    std::cout << std::setw(10) <<"" << "hand -- Describe all cards in your hand." << std::endl;
    std::cout << std::setw(10) <<"" << "board -- Describe all cards on the board." << std::endl;
}
