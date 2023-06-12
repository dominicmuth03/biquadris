#ifndef _SBLOCK_
#define _SBLOCK_

#include <vector>
#include <map>
#include <memory>
#include "block.h"

class SBlock final : public Block
{
    static std::map<int, std::vector<std::vector<int>>> spawnStates;
public:
    SBlock(int lvl) noexcept;

    std::vector<std::vector<int>> clockwise() override;
    std::vector<std::vector<int>> counterClockwise() override;
};

#endif
