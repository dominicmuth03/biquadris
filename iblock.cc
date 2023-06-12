#include <vector>
#include "block.h"
#include "iblock.h"
#include "coordinates.h"

#define up -1
#define down 1
#define left -1
#define right 1

using namespace std;

// maps clockwise, counterclockwise states

map<int, vector<vector<int>>> IBlock::spawnStates = {
    {0, {{0,3},{1,3},{2,3},{3,3}}},
    {1, {{0,3},{0,2},{0,1},{0,0}}},
    {2, {{0,3},{1,3},{2,3},{3,3}}},
    {3, {{0,3},{0,2},{0,1},{0,0}}}
};


//spawn states
/*map<int, vector<vector<int>>> IBlock::spawnStates = {
    {0, {{},{},{},{}}},
    {1, {{},{},{},{}}},
    {2, {{},{},{},{}}},
    {3, {{},{},{},{}}}
};*/

IBlock::IBlock(int lvl) noexcept : Block{'I', lvl}
{
    vector<Coordinates> coords;
    Coordinates a(0, 3);
    Coordinates b(1, 3);
    Coordinates c(2, 3);
    Coordinates d(3, 3);
    coords.emplace_back(a);
    coords.emplace_back(b);
    coords.emplace_back(c);
    coords.emplace_back(d);
    setCoords(coords);
}


vector<vector<int>> IBlock::clockwise()
{
    int r = getState() % 2; // since IBLocks can only have two states
    setState(getState() + 1);
    int dr = getState() % 2;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
    /* return rotationStates[0][r]; */
}

vector<vector<int>> IBlock::counterClockwise()
{
    int r = getState() % 2; // since IBLocks can only have two states
    setState(getState() + 3);
    int dr = getState() % 2;
    vector<vector<int>> retVal = vviSubtraction(spawnStates[dr], spawnStates[r]);
    return retVal;
}

