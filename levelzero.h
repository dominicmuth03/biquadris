#ifndef _LEVELZERO_
#define _LEVELZERO_

#include <vector>
#include "level.h"

class LevelZero : public Level
{
public:
    LevelZero(int seed, std::vector<char> sequence);
    char generateBlock() override;
};

#endif
