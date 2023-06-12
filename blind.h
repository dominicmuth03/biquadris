#ifndef _BLIND_
#define _BLIND_

#include <memory>
#include <vector>
#include "effectdecorator.h"

class AbstractBoard;

class Blind : public EffectDecorator
{
    std::vector<char> state;

    void apply() override; // applies the blind effect to getState()

public:
    Blind(std::unique_ptr<AbstractBoard> component);
    ~Blind() override;

    char getNext() override;
    std::vector<char> getState() override;
    int getCleared() override;

    std::shared_ptr<Block> makeBlock(char c) override;
    void setBlock(std::shared_ptr<Block> &block) override;
    void setLevel(int level) override;
    void setRandom(bool isRandom) override;
    void setSequence(std::vector<char> newSequence) override;

    void setup() override;

    void clockwise() override;
    void counterClockwise() override;
    void right() override;
    void left() override;
    int down() override;
    int drop() override;

};

#endif
