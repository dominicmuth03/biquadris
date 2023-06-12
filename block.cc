#include <map>
#include "block.h"

using namespace std;

struct Block::BlockImpl
{
    char c;
    int lvl, age, maxAge, rotationState;
    bool isHeavy, decays; // heavinesss based on level
    std::vector<Coordinates> coords;

    BlockImpl(char c, int lvl, bool decays) noexcept;
    ~BlockImpl() noexcept = default;

    Coordinates &getCoords();
};

Block::BlockImpl::BlockImpl(char c, int lvl, bool decays) noexcept : c{c}, lvl{lvl}, age{0}, maxAge{((decays) ? 10 : -1)}, rotationState{0}, isHeavy{((lvl >= 3) ? true : false)}, decays{decays} {}

Block::Block(char c, int lvl, bool decays) noexcept : impl{make_unique<Block::BlockImpl>(c, lvl, decays)} {}

Block::~Block() noexcept = default;

int Block::getState() { return impl->rotationState; }

char Block::getChar() { return impl->c; }

int Block::getLvl() { return impl->lvl; }

bool Block::fullCleared()
{
    for (Coordinates & coord : impl->coords)
    {
        if (!coord.removed()) return false;
    }
    return true;
}

vector<Coordinates> Block::getCoords() { return impl->coords; }

void Block::setCoords(std::vector<Coordinates> &coords) { impl->coords = coords; }

void Block::setState(int newState) { impl->rotationState = newState; }

bool Block::isHeavy() { return impl->isHeavy; }

vector<vector<int>> Block::right() 
{
    vector<vector<int>> transform = {{1, 0}, {1, 0}, {1, 0}, {1, 0}};
    return transform;
}

vector<vector<int>> Block::left() 
{
    vector<vector<int>> transform = {{-1, 0}, {-1, 0}, {-1, 0}, {-1, 0}};
    return transform;
}

vector<vector<int>> Block::down() 
{
    vector<vector<int>> transform = {{0, 1}, {0, 1}, {0, 1}, {0, 1}};
    return transform;
}

// doesnt move blocks down
bool Block::decay()
{
    if (!impl->decays) return false;
    impl->age++;
    if (impl->age == impl->maxAge)
    {
        for (Coordinates coord : impl->coords)
        {
            coord = Coordinates{-1, -1};
        }
        return true;
    }
    return false;
}

void Block::updateCoords(Coordinates oldCoords, Coordinates newCoords)
{
    int len = impl->coords.size();
    for (int i = 0; i < len; i++)
    {
        if (impl->coords[i] == oldCoords) impl->coords[i] = newCoords;
    }
}

void Block::update(std::vector<std::vector<int>> transform)
{
    int len = transform.size();
    for (int i = 0; i < len; i++)
    {
        impl->coords[i].update(transform[i][0], transform[i][1]);
    }
}

vector<vector<int>> Block::vviAddition(const vector<vector<int>> a, const vector<vector<int>> b) {
    vector<vector<int>> retVal;
    for (int i = 0; i < 4; i++) {
        vector<int> temp = {a[i][0] + b[i][0],
            a[i][1] + b[i][1]};
        retVal.emplace_back(temp);
    };
    return retVal;
}

vector<vector<int>> Block::vviSubtraction(const vector<vector<int>> a, const  vector<vector<int>> b) {
    vector<vector<int>> retVal;
    for (int i = 0; i < 4; i++) {
        vector<int> temp = {a[i][0] - b[i][0],
            a[i][1] - b[i][1]};
        retVal.emplace_back(temp);
    };
    return retVal;
}

vector<vector<int>> Block::getVVICoords() {
    vector<vector<int>> retVal;
    vector<Coordinates> tempC = getCoords();
    for (int i = 0; i < 4; i++) {
        vector<int> temp = {tempC[i].getX(), tempC[i].getY()};
        retVal.emplace_back(temp);
    }
    return retVal;
}
