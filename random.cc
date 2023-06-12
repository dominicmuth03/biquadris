#include "random.h"

Random::Random(int seed)
{
    srand(seed);
}

int Random::getRand(int mod) { return rand() % mod; }
