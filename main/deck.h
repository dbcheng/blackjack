#include <string>
#include <sstream>
#include <cassert>
#include <vector>
#include <map>
#include <algorithm>
#include <random>


std::map<std::string, int> kRanks {
    {"Two", 2},
    {"Three", 3},
    {"Four", 4},
    {"Five", 5},
    {"Six", 6},
    {"Seven", 7},
    {"Eight", 8},
    {"Nine", 9},
    {"Ten", 10},
    {"Jack", 10},
    {"Queen", 10},
    {"King", 10},
    {"Ace", 11}
    // TODO: Add Jokers
};

std::vector<std::string> kSuits {
    "Club",
    "Diamond",
    "Heart",
    "Spade"
};

struct Card {
    std::string rank;   
    int value;
    std::string suit;

    std::string Display() const{
        std::stringstream s;
        s << rank << " of " << suit;
        return s.str();
    }
};

class Deck {
 public:
     Deck() {
         for (const auto& [rank, value] : kRanks) {
             for (const std::string& suit : kSuits) {
                 cards_.push_back(Card{.rank=rank, .value=value, .suit=suit});
             }
         }
        auto rd = std::random_device {};
        auto rng = std::default_random_engine { rd() };
        std::shuffle(std::begin(cards_), std::end(cards_), rng);
        init_size_ = cards_.size();
     };

     int Size() const {
         return cards_.size();
     }

     // Up to the caller to check cards size?
     Card Next() {
         assert(!cards_.empty());
         Card next_card = cards_[0];
         cards_.erase(cards_.begin());
         used_cards_.push_back(next_card);
         return next_card;
     };

     void Reset() {
         for (const Card& card : used_cards_) {
             cards_.push_back(card);
         }
         used_cards_.clear();
         assert(used_cards_.empty());
         assert((int)cards_.size() == init_size_);
     }

     int InitSize() const {
         return init_size_;
     };

     std::string Display() const {
        std::stringstream result;
        for (int i = 0; i < (int)cards_.size(); i++) {
            result << "Card " << i+1 << ": "<< cards_[i].Display() << std::endl;
        }
        return result.str();
     }

 private:
     std::vector<Card> cards_;
     std::vector<Card> used_cards_;
     int init_size_;

};
