#ifndef _RANDOM_
#define _RANDOM_

#include <cstdlib>

// use by making a Random object in class, and call getRand to produce randInt
class Random
{
public:
    Random(int seed=1); // default random seed of 1

    int getRand(int mod); // gets random number
};

#endif
