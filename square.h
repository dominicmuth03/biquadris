#ifndef _SQUARE_
#define _SQUARE_

#include <memory>
#include "coordinates.h"
#include "block.h"

class Square
{
    Coordinates c;
    std::shared_ptr<Block> block;

public:
    Square(int x, int y);

    char getChar();                     // returns the char of the piece occupying the square
    std::shared_ptr<Block> &getBlock(); // returns the block occupying the square
    Coordinates &getCoords();           // returns the coordinates of square

    void setBlock(std::shared_ptr<Block> &newBlock); // sets the current block occupying the square
    void setCoords(Coordinates &newCoord);           // sets c to newCoord
    void removeBlock();                              // removes the block at square
};

#endif
