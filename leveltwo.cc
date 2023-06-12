#include "leveltwo.h"
#include "random.h"

#define toUpper(c) (char)(('a' <= c && c <= 'z') ? (c - 'a' + 'A') : c)

using namespace std;

LevelTwo::LevelTwo(int seed, vector<char> sequence) : Level{seed, 2, false, sequence}, randNum{Random{seed}} {}

char LevelTwo::generateBlock()
{
    int random = randNum.getRand(7);
    if (random == 0)
    {
        return 'S';
    }
    else if (random == 1)
    {
        return 'Z';
    }
    else if (random == 2)
    {
        return 'I';
    }
    else if (random == 3)
    {
        return 'J';
    }
    else if (random == 4)
    {
        return 'L';
    }
    else if (random == 5)
    {
        return 'O';
    }
    else
    {
        return 'T';
    }
}