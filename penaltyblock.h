#ifndef _PENALTYBLOCK_
#define _PENALTYBLOCK_

#include "block.h"

class PenaltyBlock : public Block
{
    
public:
    PenaltyBlock();
    
    std::vector<std::vector<int>> clockwise() override;
    std::vector<std::vector<int>> counterClockwise() override;
};

#endif
