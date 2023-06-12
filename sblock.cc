#include <vector>
#include "block.h"
#include "sblock.h"
#include "coordinates.h"

#define up -1
#define down 1
#define left -1
#define right 1

using namespace std;
// SHORTEN THIS TO TWO STATES LATER


map<int, vector<vector<int>>> SBlock::spawnStates = {
    {0, {{0, 3}, {1,3}, {1,2}, {2,2}}},
    {1, {{0,1},{0,2},{1,2},{1,3}}},
    {2, {{0, 3}, {1,3}, {1,2}, {2,2}}},
    {3, {{0,1},{0,2},{1,2},{1,3}}}
};

SBlock::SBlock(int lvl) noexcept : Block{'S', lvl}
{
    vector<Coordinates> coords;
    Coordinates a(0, 3);
    Coordinates b(1, 3);
    Coordinates c(1, 2);
    Coordinates d(2, 2);
    coords.emplace_back(a);
    coords.emplace_back(b);
    coords.emplace_back(c);
    coords.emplace_back(d);
    setCoords(coords);
};

vector<vector<int>> SBlock::clockwise()
{
    int r = getState() % 4;
    setState(getState() + 1);
    int dr = getState() % 4;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}

vector<vector<int>> SBlock::counterClockwise()
{
    int r = getState() % 4;
    setState(getState() + 3);
    int dr = getState() % 4;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}
