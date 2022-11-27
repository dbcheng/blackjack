#include <iostream>
#include <string>
#include <vector>


struct Card {
    
};

int main(void) {
    std::cout << "blackjack compiling with C++ version: "<< __cplusplus << std::endl;
    std::vector<std::string> v = {"foo", "bar", "baz"};
    std::cout << "v: "<< v[0] << std::endl;

    return 0;
}
