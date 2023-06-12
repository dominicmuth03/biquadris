#include "levelzero.h"

#define toUpper(c) (char)(('a' <= c && c <= 'z') ? (c - 'a' + 'A') : c)

LevelZero::LevelZero(int seed, std::vector<char> sequence) : Level{seed, 0, false, sequence} {}

char LevelZero::generateBlock()
{
    if (i == len) i = 0;
    char out = sequence[i];
    i++;
    return toUpper(out);
}
