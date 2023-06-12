#include <vector>
#include "block.h"
#include "zblock.h"
#include "coordinates.h"

#define up -1
#define down 1
#define left -1
#define right 1

using namespace std;

map<int, vector<vector<int>>> ZBlock::spawnStates = {
    {0, {{0,2},{1,2},{1,3},{2,3}}},
    {1, {{1,1},{1,2},{0,2},{0,3}}},
    {2, {{0,2},{1,2},{1,3},{2,3}}},
    {3, {{1,1},{1,2},{0,2},{0,3}}},
};

ZBlock::ZBlock(int lvl) noexcept : Block{'Z', lvl}
{
    vector<Coordinates> coords;
    Coordinates a(0, 2);
    Coordinates b(1, 2);
    Coordinates c(1, 3);
    Coordinates d(2, 3);
    coords.emplace_back(a);
    coords.emplace_back(b);
    coords.emplace_back(c);
    coords.emplace_back(d);
    setCoords(coords);
}

vector<vector<int>> ZBlock::clockwise()
{
    int r = getState() % 4;
    setState(getState() + 1);
    int dr = getState() % 4;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}


vector<vector<int>> ZBlock::counterClockwise()
{
    int r = getState() % 4;
    setState(getState() + 3);
    int dr = getState() % 4;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}