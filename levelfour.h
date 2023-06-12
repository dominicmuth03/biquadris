#ifndef _LEVELFOUR_
#define _LEVELFOUR_

#include <vector>
#include "level.h"
#include "random.h"

class LevelFour : public Level
{
    Random randNum;

public:
    LevelFour(int seed, std::vector<char> sequence);

    char generateBlock() override;
};

#endif
