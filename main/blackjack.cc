#include <iostream>
#include <string>
#include <vector>
#include "deck.h"




int main(void) {
    std::cout << "blackjack compiling with C++ version: "<< __cplusplus <<
        std::endl;

    std::string cmd;
    std::cout << "Start Playing? (y/n): ";
    std::cin >> cmd;
    while (cmd != "n") {
        // Do hand
        //
        
        std::cout << "Start Next Hand? (y/n): ";
        std::cin >> cmd;
    }
    
    Deck deck;
    
    while (deck.Size()) {
        std::cout << deck.Next().Display() << std::endl;
    }



    return 0;
}
