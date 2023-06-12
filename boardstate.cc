#include <algorithm>
#include "boardstate.h"
#include "exceptions.h"

#define width 11
#define height 18

#define neg(x) (-1 * (x))
#define squared(x) (x)*(x)

using namespace std;

BoardState::BoardState(int lvl) : lvl{lvl}, totalCleared{0}, block{nullptr}
{
    for (int x = 0; x < width; x++)
    {
        floor.emplace_back(height - 1);
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            state.emplace_back(Square{x, y});
        }
    }
}

// clears the block from square and sets that block's coordinate at square to (-1, -1)
void BoardState::clearSquare(Coordinates &c) 
{
    state[c.index()].getBlock()->updateCoords(c);
    state[c.index()].removeBlock();
}

void BoardState::swap(Square &target, Square &dest)
{
    shared_ptr<Block> temp = target.getBlock();
    Coordinates tempCoords = target.getCoords();

    target.setBlock(dest.getBlock());
    target.setCoords(dest.getCoords());
    dest.setBlock(temp);
    dest.setCoords(tempCoords);
}

bool BoardState::isSafe(vector<vector<int>> transform)
{
    int len = transform.size();
    for (int i = 0; i < len; i++)
    {
        Coordinates temp = block->getCoords()[i];
        temp.update(transform[i][0], transform[i][1]);

        // check if block is out of bounds
        if (temp.getX() < 0 || temp.getX() >= width || temp.getY() < 0 || temp.getY() >= height)
        {
            return false;
        }

        // if new spot is already filled
        if (state[temp.index()].getChar() != ' ')
        {
            bool safe = false;
            for (Coordinates coord : block->getCoords())
            {
                if (temp == coord)
                {
                    safe = true;
                    break;
                }
            }
            if (!safe) return false;
        }
    }
    return true;
}

vector<char> BoardState::getState()
{
    vector<char> out;
    for (Square square : state)
    {
        out.emplace_back(square.getChar());
    }
    return out;
}

bool BoardState::checkRow(int row)
{
    for (int x = 0; x < width; x++)
    {
        Coordinates square{x, row};
        if (state[square.index()].getChar() == ' ') return false;
    }
    return true;
}

int BoardState::onFloor()
{
    bool on = false;
    // checks if the piece is on the floor
    for (Coordinates coord : block->getCoords())
    {
        if (coord.removed()) continue;
        if (coord.getY() == floor[coord.getX()])
        {
            on = true;
            break;
        }
    }
    if (!on) return 0;

    // check if any rows need to cleared
    int score = 0;
    int rowsCleared = 0;
    vector<int> yCoords;
    for (Coordinates coord : block->getCoords())
    {
        yCoords.emplace_back(coord.getY());
    }
    int len = yCoords.size();
    for (int i = len - 1; i >= 0; i--)
    {
        if (checkRow(yCoords[i]))
        {
            rowsCleared++;
            score += clearRow(yCoords[i]);
        }
    }

    // if the piece is on the floor, set new floor height
    for (Coordinates coord : block->getCoords())
    {
        if (coord.removed()) continue;
        floor[coord.getX()] = (floor[coord.getX()] > coord.getY()) ? coord.getY() : floor[coord.getX()];
    }
    score += squared(lvl + rowsCleared);
    totalCleared += rowsCleared;
    return score;
}

int BoardState::rowScore(vector<shared_ptr<Block>> cleared)
{
    // points for clearing a line
    int score = 0;
    vector<shared_ptr<Block>> scored;
    for (shared_ptr<Block> block : cleared)
    {
        // points for full clearing a block that hasn't already been cleared
        if (block->fullCleared() && (find(scored.begin(), scored.end(), block) == scored.end()))
        {
            score += squared(block->getLvl() + 1);
            scored.emplace_back(block);
        }
    }
    return score;
}

int BoardState::clearRow(int row)
{
    vector<shared_ptr<Block>> cleared;
    // clearing row
    for (int x = 0; x < width; x++)
    {
        Coordinates target{x, row};
        cleared.emplace_back(state[target.index()].getBlock());
        clearSquare(target);
    }
    int score = rowScore(cleared);
    // shift rows above down
    for (int y = row; y >= 3; y--)
    {
        // for every element in row, swap with element in row above
        for (int x = 0; x < width; x++)
        {
            int i = (width * y) + x;
            swap(state[i], state[i - width]);
        }
    }
    return score;
}

void BoardState::initBlock(std::shared_ptr<Block> currBlock)
{
    // get ride of old block
    if (block != nullptr)
    {
        for (Coordinates coord : block->getCoords())
        {
            state[coord.index()].removeBlock();
        }
    }
    // initialize new block onto boardstate
    block = currBlock;
    for (Coordinates coord : block->getCoords())
    {
        if (state[coord.index()].getChar() != ' ') throw game_over{};
        state[coord.index()].setBlock(block);
    }
}

void BoardState::apply(vector<vector<int>> transform, bool playerMove)
{
    if(!isSafe(transform))
    {
        if (!playerMove) return;
        throw invalid_move{};
    }

    for (Coordinates coord : block->getCoords())
    {
        state[coord.index()].removeBlock();
    }
    block->update(transform);
    for (Coordinates coord : block->getCoords())
    {
        state[coord.index()].setBlock(block);
    }

    // handles level heaviness
    if (block->isHeavy() && playerMove) apply(block->down(), false);
}

int BoardState::getCleared() { return totalCleared; }

void BoardState::clockwise()
{
    if (block == nullptr) return;
    apply(block->clockwise());
}

void BoardState::counterClockwise()
{
    if (block == nullptr) return;
    apply(block->counterClockwise());
}

void BoardState::left()
{
    if (block == nullptr) return;
    apply(block->left());
}

void BoardState::right()
{
    if (block == nullptr) return;
    apply(block->right());
}

int BoardState::down()
{   
    if (block == nullptr) return 0;
    apply(block->down());
    return onFloor();
}

int BoardState::drop()
{   
    if (block == nullptr) return 0;
    int score = 0;
    for (int y = 3; y < height - 1; y++)
    {
        apply(block->down(), false);
        score += onFloor();
        if (score > 0) break;
    }

    // adding the block to the placed block list
    placed.emplace_back(block);
    block = nullptr;

    // handles decaying the block
    for (shared_ptr<Block> b : placed)
    {
        if (b->decay())
        {
            for (Coordinates coord : b->getCoords())
            {
                state[coord.index()].removeBlock();
                b->updateCoords(coord);
            }
        }
    }
    return score;
}
