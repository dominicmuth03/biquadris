#include <memory>
#include "blind.h"
#include "abstractboard.h"

#define width 11
#define height 18

using namespace std;

Blind::Blind(unique_ptr<AbstractBoard> component) : EffectDecorator{move(component)} {}

Blind::~Blind() {}

void Blind::apply()
{
    for (int y = 3; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x >= 2 && x < 9 && y >= 6 && y <= 15)
            {
                state[(y * width) + x] = '?';
            }
        }
    }
}

char Blind::getNext() { return component->getNext(); }

vector<char> Blind::getState()
{
    state = component->getState();
    apply();
    return state;
}

int Blind::getCleared() { return component->getCleared(); }

shared_ptr<Block> Blind::makeBlock(char c) { return component->makeBlock(c); }

void Blind::setBlock(shared_ptr<Block> &block) { component->setBlock(block); }

void Blind::setLevel(int level) { component->setLevel(level); }

void Blind::setRandom(bool isRandom) { component->setRandom(isRandom); }

void Blind::setSequence(std::vector<char> newSequence) { component->setSequence(newSequence); }

void Blind::setup() { component->setup(); }

void Blind::clockwise() { component->clockwise(); }

void Blind::counterClockwise() { component->counterClockwise(); }

void Blind::left() { component->left(); }

void Blind::right() { component->right(); }

int Blind::down() { return component->down(); }

int Blind::drop() { return component->drop(); }
