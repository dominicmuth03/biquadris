#include <memory>
#include "force.h"
#include "abstractboard.h"

using namespace std;

Force::Force(unique_ptr<AbstractBoard> component, char forcedBlock) : EffectDecorator{move(component)}, forcedBlock{forcedBlock} {}

Force::~Force() {}

void Force::apply()
{
    shared_ptr<Block> block = component->makeBlock(forcedBlock);
    component->setBlock(block);
}

char Force::getNext() { return component->getNext(); }

vector<char> Force::getState() { return component->getState(); }

int Force::getCleared() { return component->getCleared(); }

shared_ptr<Block> Force::makeBlock(char c) { return component->makeBlock(c); }

void Force::setBlock(shared_ptr<Block> &block) { component->setBlock(block); }

void Force::setLevel(int level) { component->setLevel(level); }

void Force::setRandom(bool isRandom) { component->setRandom(isRandom); }

void Force::setSequence(vector<char> sequence) { component->setSequence(sequence); }

void Force::setup() 
{
    apply();
}

void Force::clockwise() { component->clockwise(); }

void Force::counterClockwise() { component->counterClockwise(); }

void Force::left() { component->left(); }

void Force::right() { component->right(); }

int Force::down() { return component->down(); }

int Force::drop() { return component->drop(); }
