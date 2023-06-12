#ifndef _ABSBOARD_
#define _ABSBOARD_

#include <memory>
#include <string>
#include "block.h"

class AbstractBoard
{
public:
    std::unique_ptr<AbstractBoard> component;

    AbstractBoard(std::unique_ptr<AbstractBoard> component=nullptr) noexcept;
    ~AbstractBoard() noexcept;

    // pure virtual getter methods
    virtual char getNext() = 0;
    virtual std::vector<char> getState() = 0;
    virtual int getCleared() = 0;

    // pure virtual block manipulation methods
    virtual std::shared_ptr<Block> makeBlock(char c) = 0;
    virtual void setBlock(std::shared_ptr<Block> &block) = 0;
    virtual void setLevel(int level) = 0;
    virtual void setRandom(bool isRandom) = 0;
    virtual void setSequence(std::vector<char> newSequence) = 0;

    virtual void setup() = 0;

    // pure virtual transform methods
    virtual void counterClockwise() = 0;
    virtual void clockwise() = 0;
    virtual void right() = 0;
    virtual void left() = 0;
    virtual int down() = 0;
    virtual int drop() = 0;
};

#endif
