#ifndef _LEVELTHREE_
#define _LEVELTHREE_

#include <vector>
#include "level.h"
#include "random.h"

class LevelThree : public Level
{
    Random randNum;

public:
    LevelThree(int seed, std::vector<char> sequence);
    
    char generateBlock() override;
};

#endif
