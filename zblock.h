#ifndef _ZBLOCK_
#define _ZBLOCK_

#include <vector>
#include <map>
#include <memory>
#include "block.h"

class ZBlock : public Block
{
    static std::map<int, std::vector<std::vector<int>>> spawnStates;
public:
    ZBlock(int lvl) noexcept;
    
    std::vector<std::vector<int>> clockwise() override;
    std::vector<std::vector<int>> counterClockwise() override;
};

#endif
