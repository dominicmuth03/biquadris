#include "level.h"

using namespace std;

Level::Level(int seed, int lvl, bool isRandom, vector<char> sequence) : seed{seed}, lvl{lvl}, i{0}, isRandom{isRandom}, sequence{sequence} 
{
    len = sequence.size();
}

int Level::getLvl() { return lvl; }

void Level::setRandom(bool newValue) { isRandom = newValue; }

void Level::setSequence(vector<char> newSequence) { 
    sequence = newSequence; 
    i = 0;
    len = sequence.size();
}