#ifndef _BOARDSTATE_
#define _BOARDSTATE_

#include <vector>
#include <memory>
#include "block.h"
#include "coordinates.h"
#include "square.h"

class BoardState
{
    int lvl, totalCleared;
    std::vector<Square> state;
    std::vector<int> floor;
    std::shared_ptr<Block> block;
    std::vector<std::shared_ptr<Block>> placed;

    void clearSquare(Coordinates &c);        // clears the square at c
    void swap(Square &target, Square &dest); // swaps target and dest squares
    void move(Square &target, Square &dest); // moves target to dest

    void apply(std::vector<std::vector<int>> transform, bool playerMove = true); // applies transform to block

    bool isSafe(std::vector<std::vector<int>> transform);      // checks if a transformation is safe
    int rowScore(std::vector<std::shared_ptr<Block>> cleared); // returns the score of clearing the caller

    int onFloor(); // checks whether the current block is on the floor, returns score if on floor

    // row functions
    bool checkRow(int row); // returns whether row is filled
    int clearRow(int row);  // clears all squares on row and returns the score for clearing the row

public:
    BoardState(int lvl);

    // getter functions
    std::vector<char> getState(); // returns the state
    int getCleared(); // returns total rows cleared

    // setter functions
    void initBlock(std::shared_ptr<Block> currBlock); // initializes the block to the boardstate

    // block transformations (update the square's block + update block coords)
    void clockwise();
    void counterClockwise();
    void left();
    void right();

    int down(); // additionally returns score if rows are cleared
    int drop();
};

#endif
