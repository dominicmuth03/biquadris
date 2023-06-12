#include <vector>
#include "block.h"
#include "jblock.h"
#include "coordinates.h"

#define up -1
#define down 1
#define left -1
#define right 1

using namespace std;

// maps clockwise, counterclockwise states

map<int, vector<vector<int>>> JBlock::spawnStates = {
    {0, {{0,2},{0,3},{1,3},{2,3}}},
    {1, {{1,1},{0,1},{0,2},{0,3}}},
    {2, {{2,3},{2,2},{1,2},{0,2}}},
    {3, {{1,3},{1,2},{1,1},{0,3}}}
};

JBlock::JBlock(int lvl) noexcept : Block{'J', lvl}
{
    vector<Coordinates> coords;
    Coordinates a(0, 2);
    Coordinates b(0, 3);
    Coordinates c(1, 3);
    Coordinates d(2, 3);
    coords.emplace_back(a);
    coords.emplace_back(b);
    coords.emplace_back(c);
    coords.emplace_back(d);
    setCoords(coords);
}

vector<vector<int>> JBlock::clockwise()
{
    int r = getState() % 4;
    setState(getState() + 1);
    int dr = getState() % 4;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}

vector<vector<int>> JBlock::counterClockwise()
{
    int r = getState() % 4;
    setState(getState() + 3);
    int dr = getState() % 4;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}
