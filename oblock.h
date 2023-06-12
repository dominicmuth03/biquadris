#ifndef _OBLOCK_
#define _OBLOCK_

#include <vector>
#include <map>
#include <memory>
#include "block.h"

class OBlock : public Block
{
    static std::map<int, std::vector<std::vector<int>>> spawnStates;
public:
    OBlock(int lvl) noexcept;

    std::vector<std::vector<int>> clockwise() override;
    std::vector<std::vector<int>> counterClockwise() override;
};

#endif
