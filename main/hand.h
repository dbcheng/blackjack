#include <sstream>
#include <iostream>
#include<unistd.h>               // for linux

int kDefaultBet = 10;

struct Player {
    std::string name;
    int money;
};

class Hand {
 public:
    Hand(Player* player, Deck* deck) : player_(player), deck_(deck) {};

    void Run() {
        std::cout << "Starting hand!" << std::endl;

        if (deck_->Size() < (deck_->InitSize() / 4)) {
            std::cout << "Deck is too small, reshuffling..." << std::endl;
            deck_->Reset();
        }
        
        player_hand_.push_back(deck_->Next());
        dealer_hand_.push_back(deck_->Next());
        player_hand_.push_back(deck_->Next());
        dealer_hand_.push_back(deck_->Next());

        bool hide_dealer_card = true;
        std::cout << Display(hide_dealer_card) << std::endl;

        // Player Turn
        std::vector<std::string> options = {"h", "d", "st"};
        // TODO: Implement Splits
        //if (player_hand_[0].rank == player_hand[1].rank) {
        //    options.push_back("s");
        //}

        int bet = kDefaultBet;

        std::string cmd;
        std::cout << "Player Options (h/d/st):";
        std::cin >> cmd;
        while (std::find(options.begin(), options.end(), cmd) == options.end()) {
            std::cout << "Unknown command (" << cmd << "). Please try again" << std::endl;
            std::cout << "Player Options (h/d/st):";
            std::cin >> cmd;
        }

        if (cmd == "h") {
            player_hand_.push_back(deck_->Next());
            std::cout << Display(hide_dealer_card) << std::endl;
            while (Score(player_hand_) < 21) {
                // Hit
                std::cout << "Player Options (h/st):";
                std::cin >> cmd;
                if (cmd == "h") {
                    player_hand_.push_back(deck_->Next());
                    std::cout << Display(hide_dealer_card) << std::endl;
                } else {
                    break;
                }
            }
        } else if (cmd == "d") {
            // TODO: kDouble Bet.
            bet *= 2;
            player_hand_.push_back(deck_->Next());
        }      
        std::cout << Display(hide_dealer_card) << std::endl;

        int player_score = Score(player_hand_);
        if (player_score > 21) {
            std::cout << "Player Busted!" << std::endl; 
            TakeMoney(bet);
            return;
        }


        // Dealer Turn
        hide_dealer_card = false;
        while (Score(dealer_hand_) < 17) {
            dealer_hand_.push_back(deck_->Next());
            std::cout << Display(hide_dealer_card) << std::endl;
        }

        std::cout << Display(hide_dealer_card) << std::endl;
        int dealer_score = Score(dealer_hand_);
        if (dealer_score > 21) {
            std::cout << "Dealer Busted!" << std::endl; 
            GiveMoney(bet);
            return;
        }

        if (dealer_score > player_score) {
            std::cout << "Dealer Wins :(" << std::endl; 
            // TODO Take Money
            TakeMoney(bet);
        } else if (player_score > dealer_score) {
            std::cout << "Player Wins :)" << std::endl; 
            GiveMoney(bet);
        } else {
            std::cout << "PUSH" << std::endl; 
        }
    };
    
    std::string Display(bool hide_dealer_card) {
        std::stringstream hand_display;
        hand_display << "\n\n*******************************\n\n" << std::endl; 
        hand_display << "Dealer's Cards: " << std::endl; 
        for (int i = 0; i < (int) dealer_hand_.size(); i++) {
            if (i == 0 && hide_dealer_card) {
                hand_display << "\t** of **" << std::endl;    
                continue;
            }
            hand_display << "\t" << dealer_hand_[i].Display() << std::endl;    
        }
        hand_display << std::endl; 
        hand_display << "Player's Cards: " << std::endl; 
        for (const Card& card : player_hand_) {
            hand_display << "\t" << card.Display() << std::endl;    
        }
        hand_display << "\n\n*******************************\n\n" << std::endl; 
        sleep(1);
        return hand_display.str();
    };


 private:
    void TakeMoney(int money) {
        player_->money -= money;        
    }
    void GiveMoney(int money) {
        player_->money += money;        
    }

    int Score(const std::vector<Card>& cards) {
        int score = 0;
        int num_aces = 0;
        for (const Card& card : cards) {
            score += card.value;
            if (card.rank == "Ace") {
                num_aces++;
            }
        }
        if (score > 21 && num_aces > 0) {
            score -= 10;
            num_aces--;
        }
        return score;
    };

    Player* player_; // not owned
    Deck* deck_; // not owned
    std::vector<Card> dealer_hand_;
    std::vector<Card> player_hand_;
};
