#ifndef RANDOMINT_HPP
#define RANDOMINT_HPP

#include <chrono>
#include <random>

// 随机正数发生器，提供[min, max]域里的整数

class RandomInt {

    std::uniform_int_distribution<int> distribution;
    std::mt19937_64 generator;

public:

    RandomInt(int min, int max);
    int get();

};


#endif // RANDOMINT_HPP
