#include <iostream>
#include <string>
#include <vector>
#include "deck.h"
#include "hand.h"

int kInitMoney = 100;

int main(void) {
    std::cout << "blackjack compiling with C++ version: "<< __cplusplus <<
        std::endl;


    Deck deck;
    Player player = {.name="David", .money=kInitMoney};
    std::cout << "Player: " << player.name << " has $" << player.money << std::endl;
    std::string cmd;
    std::cout << "Start Playing? (y/n): ";
    std::cin >> cmd;
    while (cmd != "n") {
        std::cout << "=============================" << std::endl;
        if (player.money < 10) {
            std::cout << "Not enough money. Min Bet: $10";
        }
        std::cout << "Start Next Hand? (y/n): ";
        std::cin >> cmd;
        if (cmd == "y") {
            Hand hand(&player, &deck);
            hand.Run();

            std::cout << "Player: " << player.name << " has $" << player.money << std::endl;
        }
    }
    
    return 0;
}
