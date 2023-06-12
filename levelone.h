#ifndef _LEVELONE_
#define _LEVELONE_

#include <vector>
#include "level.h"
#include "random.h"

class LevelOne : public Level
{
    Random randNum;

public:
    LevelOne(int seed, std::vector<char> sequence);

    char generateBlock() override;
};

#endif
