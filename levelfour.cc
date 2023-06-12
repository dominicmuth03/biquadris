#include "levelfour.h"
#include "random.h"
#include <vector>

using namespace std;

#define toUpper(c) (char)(('a' <= c && c <= 'z') ? (c - 'a' + 'A') : c)

LevelFour::LevelFour(int seed, vector<char> sequence) : Level{seed, 4, true, sequence}, randNum{Random{seed}} {}

char LevelFour::generateBlock()
{
    if (isRandom)
    {
        int random = randNum.getRand(9);
        if (random == 0 || random == 1)
        {
            return 'S';
        }
        else if (random == 2 || random == 3)
        {
            return 'Z';
        }
        else if (random == 4)
        {
            return 'I';
        }
        else if (random == 5)
        {
            return 'J';
        }
        else if (random == 6)
        {
            return 'L';
        }
        else if (random == 7)
        {
            return 'O';
        }
        else
        {
            return 'T';
        }
    }
    else
    {
        if (i == len) i = 0;
        char out = sequence[i];
        i++;
        return toUpper(out);
    }
}
