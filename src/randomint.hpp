#ifndef RANDOMINT_HPP
#define RANDOMINT_HPP

#include <chrono>
#include <random>

class RandomInt {

    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 generator;

public:

    RandomInt(int min, int max):
        distribution(std::uniform_int_distribution<int>(min, max)),
        generator(std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count())) {}

    int get() {
        return distribution(generator);
    }

};


#endif // RANDOMINT_HPP
