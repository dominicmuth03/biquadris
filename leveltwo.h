#ifndef _LEVELTWO_
#define _LEVELTWO_

#include <vector>
#include "level.h"
#include "random.h"

class LevelTwo : public Level
{
    Random randNum;

public:
    LevelTwo(int seed, std::vector<char> sequence);
    char generateBlock() override;
};

#endif
