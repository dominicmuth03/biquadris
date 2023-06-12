#include "square.h"

using namespace std;

Square::Square(int x, int y) : c{Coordinates{x, y}}, block{nullptr} {}

shared_ptr<Block>& Square::getBlock() { return block; }

Coordinates & Square::getCoords() { return c; }

char Square::getChar()
{
    if (block == nullptr) return ' ';
    return block->getChar();
}

void Square::setBlock(shared_ptr<Block>& newBlock) { block = newBlock; }

void Square::setCoords(Coordinates &newCoord) { c = newCoord; }

void Square::removeBlock() { block = nullptr; }
