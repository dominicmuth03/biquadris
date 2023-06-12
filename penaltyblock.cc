#include <vector>
#include "block.h"
#include "penaltyblock.h"
#include "coordinates.h"

#define MAX_LEVEL 4

using namespace std;

PenaltyBlock::PenaltyBlock() : Block{'P', MAX_LEVEL}
{
    // get floor height of middle and set coords to (5, floor)
}
void PenaltyBlock::clockwise() {}
