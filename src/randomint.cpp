#include "randomint.hpp"

RandomInt::RandomInt(int min, int max):
    distribution(std::uniform_int_distribution<int>(min, max)),
    generator(std::mt19937_64(std::chrono::system_clock::now().time_since_epoch().count())) {}

int RandomInt::get() {
    return distribution(generator);
}
