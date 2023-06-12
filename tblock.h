#ifndef _TBLOCK_
#define _TBLOCK_

#include <vector>
#include <map>
#include <memory>
#include "block.h"

class TBlock : public Block
{
    static std::map<int, std::vector<std::vector<int>>> spawnStates;
public:
    TBlock(int lvl) noexcept;
    
    std::vector<std::vector<int>> clockwise() override;
    std::vector<std::vector<int>> counterClockwise() override;
};

#endif