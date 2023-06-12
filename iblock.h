#ifndef _IBLOCK_
#define _IBLOCK_

#include <vector>
#include <map>
#include <memory>
#include "block.h"

class IBlock : public Block
{
    static std::map<int, std::vector<std::vector<int>>> spawnStates;
public:
    IBlock(int lvl) noexcept;

    std::vector<std::vector<int>> clockwise() override;
    std::vector<std::vector<int>> counterClockwise() override;
};

#endif