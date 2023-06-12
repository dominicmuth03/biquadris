#include <memory>
#include "board.h"
#include "level.h"
#include "levelzero.h"
#include "levelone.h"
#include "leveltwo.h"
#include "levelthree.h"
#include "levelfour.h"
#include "block.h"
#include "iblock.h"
#include "jblock.h"
#include "lblock.h"
#include "oblock.h"
#include "sblock.h"
#include "tblock.h"
#include "zblock.h"
#include "boardstate.h"
#include "exceptions.h"

using namespace std;

struct Board::BoardImpl
{
    int seed;
    char nextBlock;
    unique_ptr<Level> lvl;
    unique_ptr<BoardState> state;
    shared_ptr<Block> currBlock;

    shared_ptr<Block> makeBlock(char c);            // makes block of type c
    void makeLevel(int startLvl, vector<char> seq); // makes a lvl level

    void setBlock(shared_ptr<Block> &block); // sets currBlock to block
    void setLevel(int level);                // sets lvl to level

    void setup(); // sets currBlock to value of nextBlock and generates new nextBlock

    BoardImpl(int startLvl, int seed, vector<char> seq) noexcept;
    ~BoardImpl() noexcept = default;
};

void Board::BoardImpl::makeLevel(int startLvl, vector<char> seq)
{
    switch (startLvl)
    {
    case 0:
    {
        lvl = make_unique<LevelZero>(seed, seq);
        break;
    }
    case 1:
    {
        lvl = make_unique<LevelOne>(seed, seq);
        break;
    }
    case 2:
    {
        lvl = make_unique<LevelTwo>(seed, seq);
        break;
    }
    case 3:
    {
        lvl = make_unique<LevelThree>(seed, seq);
        break;
    }
    case 4:
    {
        lvl = make_unique<LevelFour>(seed, seq);
        break;
    }
    }
}

Board::BoardImpl::BoardImpl(int startLvl, int seed, vector<char> seq) noexcept : seed{seed}, state{make_unique<BoardState>(startLvl)}
{
    makeLevel(startLvl, seq);

    currBlock = makeBlock(lvl->generateBlock());
    nextBlock = lvl->generateBlock();
    state->initBlock(currBlock);
}

shared_ptr<Block> Board::BoardImpl::makeBlock(char c)
{
    shared_ptr<Block> newBlock;
    int level = lvl->getLvl();
    switch (c)
    {
    case 'I':
    {
        newBlock = make_shared<IBlock>(level);
        break;
    }
    case 'J':
    {
        newBlock = make_shared<JBlock>(level);
        break;
    }
    case 'L':
    {
        newBlock = make_shared<LBlock>(level);
        break;
    }
    case 'O':
    {
        newBlock = make_shared<OBlock>(level);
        break;
    }
    case 'S':
    {
        newBlock = make_shared<SBlock>(level);
        break;
    }
    case 'Z':
    {
        newBlock = make_shared<ZBlock>(level);
        break;
    }
    case 'T':
    {
        newBlock = make_shared<TBlock>(level);
        break;
    }
    default:
        // handle c isn't a block
        break;
    }
    return newBlock;
}

void Board::BoardImpl::setBlock(shared_ptr<Block> &block)
{
    currBlock = block;
    state->initBlock(block);

}

void Board::BoardImpl::setLevel(int level)
{
    makeLevel(level, {'L', 'S'});
}

void Board::BoardImpl::setup()
{
    currBlock = makeBlock(nextBlock);
    nextBlock = lvl->generateBlock();
    setBlock(currBlock);
}

Board::Board(int startLvl, int seed, vector<char> seq) noexcept : AbstractBoard{nullptr}, impl{make_unique<BoardImpl>(startLvl, seed, seq)} {}

Board::~Board() noexcept = default;

shared_ptr<Block> Board::makeBlock(char c) { return impl->makeBlock(c); }

void Board::setBlock(shared_ptr<Block> &block) { impl->setBlock(block); }

void Board::setLevel(int level) { impl->setLevel(level); }

void Board::setup() { impl->setup(); }

void Board::setRandom(bool isRandom) { impl->lvl->setRandom(isRandom); };

void Board::setSequence(vector<char> sequence) { impl->lvl->setSequence(sequence); }

vector<char> Board::getState() { return impl->state->getState(); }

char Board::getNext() { return impl->nextBlock; }

int Board::getCleared() { return impl->state->getCleared(); }

void Board::counterClockwise() { impl->state->counterClockwise(); }

void Board::clockwise() { impl->state->clockwise(); }

void Board::left() { impl->state->left(); }

void Board::right() { impl->state->right(); }

int Board::down() { return impl->state->down(); }

int Board::drop() { return impl->state->drop(); }
