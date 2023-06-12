#ifndef _BOARD_
#define _BOARD_

#include <memory>
#include <string>
#include <vector>
#include "abstractboard.h"
#include "block.h"

class Board : public AbstractBoard
{
    class BoardImpl;
    std::unique_ptr<BoardImpl> impl;

public:
    Board(int startLvl, int seed, std::vector<char> seq) noexcept;
    ~Board() noexcept;

    std::shared_ptr<Block> makeBlock(char c) override;     // makes a new block based on level or c
    void setBlock(std::shared_ptr<Block> &block) override; // sets current block to block
    void setLevel(int level) override;                     // sets the current level to level
    void setRandom(bool isRandom);                         // sets the randomness of board's level
    void setSequence(std::vector<char> sequence);          // sets the sequence of board's level

    // getter methods
    std::vector<char> getState() override; // returns the boardState
    char getNext() override;               // returns the next block's char
    int getCleared() override;             // returns the total number of cleared lines

    void setup() override; // sets up the following turn

    void counterClockwise() override; // rotates the block counter clockwise
    void clockwise() override;        // rotates the block clockwise
    void right() override;            // shifts the block right
    void left() override;             // shifts the block left
    int down() override;              // shifts the block down
    int drop() override;              // drops block
};

#endif
