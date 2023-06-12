#include <iostream>
#include <map>
#include <string>
#include "player.h"
#include "abstractboard.h"
#include "board.h"
#include "exceptions.h"
#include "blind.h"
#include "force.h"
#include "heavy.h"

#define MAX_LEVEL 4
#define MIN_LEVEL 0

#define toUpper(c) (char)(('a' <= c && c <= 'z') ? (c - 'a' + 'A') : c)

using namespace std;

struct Player::PlayerImpl
{
    vector<char> seq;
    static map<string, int> playerCommands;
    unique_ptr<AbstractBoard> board;
    int lvl, turns, score;
    map<string, bool> effects;
    char forcedBlock;
    vector<char> getState();

    PlayerImpl(vector<char> seq, int startLvl, int seed);
    ~PlayerImpl() = default;

    void apply();                         // applies all effects onto board
};

Player::PlayerImpl::PlayerImpl(vector<char> seq, int startLvl, int seed) : seq{seq}, lvl{startLvl}, turns{0}, score{0}, effects{{"heavy", false}, {"blind", false}, {"force", false}}
{
    board = make_unique<Board>(startLvl, seed, seq);
}

vector<char> Player::PlayerImpl::getState() {
    return board->getState();
}

vector<char> Player::getState()  {
    return impl->getState();
}

int Player::getCleared() { return impl->board->getCleared(); }



void Player::PlayerImpl::apply()
{
    for (auto const &e : effects)
    {
        // if not true, skip
        if (!e.second)
            continue;

        if (e.first == "heavy")
        {
            board = make_unique<Heavy>(move(board), 2);
        }
        else if (e.first == "blind")
        {
            board = make_unique<Blind>(move(board));
        }
        else if (e.first == "force")
        {
            // MAKE ERROR CHECKING AND GET USER INPUT FOR c
            board = make_unique<Force>(move(board), forcedBlock);
        }
    }
}

// play turn must call apply then create a sequence to read and execute user commands

Player::Player(vector<char> seq, int startLvl, int seed) : impl{make_unique<Player::PlayerImpl>(seq, startLvl, seed)} {}

Player::~Player() = default;

int Player::getLevel() { return impl->lvl; }

int Player::getScore() { return impl->score; }

char Player::getNext() { return impl->board->getNext(); }

void Player::apply() { impl->apply(); }

void Player::resetEffects()
{
    // for each effect, set it to false
    for (auto &e : impl->effects)
    {
        e.second = false;
    }

    // reset the board component to only contain the base, non-effect decorated board
    while (impl->board->component != nullptr)
    {
        impl->board = move(impl->board->component);
    }
}

void Player::setEffect(string effect)
{
    if (impl->effects.count(effect) != 0)
    {
        impl->effects[effect] = true;
    }
}

void Player::setForcedChar(char c) { impl->forcedBlock = c; }

void Player::levelUp()
{
    if (impl->lvl == MAX_LEVEL)
        throw invalid_level{MAX_LEVEL};
    impl->lvl++;
    impl->board->setLevel(impl->lvl);
}

void Player::levelDown()
{
    if (impl->lvl == MIN_LEVEL)
        throw invalid_level{MIN_LEVEL};
    impl->lvl--;
    impl->board->setLevel(impl->lvl);
}

void Player::playTurn(int cmd)
{
    shared_ptr<Block> tempBlock;
    switch (cmd)
    {
    case LEFT:
        impl->board->left();
        break;
    case RIGHT:
        impl->board->right();
        break;
    case DOWN:
        impl->score += impl->board->down();
        break;
    case CLOCKWISE:
        impl->board->clockwise();
        break;
    case COUNTERCLOCKWISE:
        impl->board->counterClockwise();
        break;
    case DROP:
        impl->score += impl->board->drop();
        break;
    case LVLUP:
        levelUp();
        break;
    case LVLDOWN:
        levelDown();
        break;
    case I:
        tempBlock = impl->board->makeBlock('I');
        impl->board->setBlock(tempBlock);
        break;
    case J:
        tempBlock = impl->board->makeBlock('J');
        impl->board->setBlock(tempBlock);
        break;
    case L:
        tempBlock = impl->board->makeBlock('L');
        impl->board->setBlock(tempBlock);
        break;
    case O:
        tempBlock = impl->board->makeBlock('O');
        impl->board->setBlock(tempBlock);
        break;
    case S:
        tempBlock = impl->board->makeBlock('S');
        impl->board->setBlock(tempBlock);
        break;
    case Z:
        tempBlock = impl->board->makeBlock('Z');
        impl->board->setBlock(tempBlock);
        break;
    case T:
        tempBlock = impl->board->makeBlock('T');
        impl->board->setBlock(tempBlock);
        break;
        
    default:
        break;
    }
}

void Player::setSequence(vector<char> newSeq) 
{ 
    impl->seq = newSeq;
    impl->board->setSequence(newSeq);
}

void Player::setRandom(bool isRandom) 
{
    impl->board->setRandom(isRandom);
}

void Player::setup() { impl->board->setup(); }


