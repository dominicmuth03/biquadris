#ifndef _GAME_
#define _GAME_

#include <memory>
#include <vector>
#include <string>
#include "commands.h"
#include "player.h"
#include "subject.h"

class Game : public Subject
{
    std::vector<std::shared_ptr<Player>> players;
    std::unique_ptr<Commands> interpreter;
    int turn;
    int seed;
    int startLvl;
    int highscore;
    bool isFinished;
    std::vector<std::string> sequences;
    std::vector<std::vector<char>> seqs;

    std::vector<char> read(std::string sequence); // reads in the file sequence and produces it as a char array

public:
    Game(int seed, int startLvl, std::vector<std::string> sequences, std::vector<bool> flagStates);
    ~Game();

    std::vector<std::shared_ptr<Player>> getPlayers();
    
    int run(); // runs the game, returns 1 if p1 wins, returns 2 if p2 wins

    void playTurn(); //plays one turn for one player

    std::vector<std::vector<char>> getState() override; // returns a vector of both player's states
};

#endif
