#ifndef _LEVEL_
#define _LEVEL_

#include <memory>
#include <vector>

class Level
{
protected:
    int seed, lvl, i, len;
    bool isRandom;
    std::vector<char> sequence;
    
public:
    Level(int seed, int lvl, bool isRandom, std::vector<char> sequence);

    // getter methods
    int getLvl(); // returns lvl
    int getSeed(); // returns seed

    void setRandom(bool newValue);
    void setSequence(std::vector<char> sequence);
    
    virtual char generateBlock() = 0; // generates a block
};

#endif
