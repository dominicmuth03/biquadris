#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include "game.h"
#include "commands.h"
#include "player.h"
#include "exceptions.h"

using namespace std;

#define toUpper(c) (char)(('a' <= c && c <= 'z') ? (c - 'a' + 'A') : c)

Game::Game(int seed, int startLvl, vector<string> sequences, vector<bool> flagStates) : interpreter{make_unique<Commands>(flagStates[1])}, turn{0}, seed{seed}, startLvl{startLvl}, highscore{0}, isFinished{false}
{
    
    int len = sequences.size();
    for (int i = 0; i < len; i++)
    {
        vector<char> seq;
        try
        {
            seq = read(sequences[i]);
        }
        catch (file_not_found &e)
        {
            seq = read(e.getDefault(i));
            cerr << e.what() << endl;
        }
        seqs.emplace_back(seq);
    }
    players.emplace_back(make_shared<Player>(seqs[0], seed, startLvl));
    players.emplace_back(make_shared<Player>(seqs[1], seed, startLvl));
}

Game::~Game() {}

vector<std::shared_ptr<Player>> Game::getPlayers()
{
    return players;
};

vector<char> Game::read(string s)
{
    vector<char> sequence;
    ifstream file{s};
    if (file.is_open())
    {
        char c;
        while (file >> c)
        {
            if (file.fail())
            {
                file.clear();
                file.ignore();
                continue;
            }
            sequence.emplace_back(c);
        }
    }
    else
    {
        throw file_not_found{s};
    }
    return sequence;
}

vector<vector<char>> Game::getState()
{
    vector<vector<char>> out;
    out.emplace_back(players[0]->getState());
    out.emplace_back(players[1]->getState());
    return out;
}

int Game::run()
{
    notifyObservers();
    // gamestate vars
    while (!isFinished)
    {
        playTurn();
    }
    int loser = turn % 2 + 1;
    int winner = (turn + 1) % 2 + 1;

    cout << "Player " << loser << " lost!" << endl;
    cout << "Player " << winner << " wins!" << endl;
    return winner; // returns 1 or 2
}

void Game::playTurn()
{
    int p = turn % 2;
    int numRows = players[p]->getCleared();
    players[p]->apply();
    cout << "Player " << p + 1 << "'s turn." << endl;
    string input;
    bool dropped = false;
    while (!dropped && !cin.eof())
    {
        cin >> input;
        vector<string> commands;
        // standard processing includes pushing the command itself to commands
        commands = interpreter->interpret(input); // interpret "preprocesses" the command
        int len = commands.size();
        for (int i = 0; i < len; i++)
        { // assume that commands in input file are all player commands
            string command = commands[i];
            if (command == "drop")
            {
                players[p]->playTurn(interpreter->playerCmd(command));
                dropped = true;
                notifyObservers();
                break;
            }
            int cmd = interpreter->gameCmd(command);
            string file;
            ifstream ifs;
            vector<char> blockSeq;
            switch (cmd)
            {
            case 0: // norandom
                cin >> file;
                ifs = ifstream{file};
                if (!ifs.good())
                {
                    throw file_not_found(file);
                }
                blockSeq = read(file);
                players[p]->setSequence(blockSeq);
                players[p]->setRandom(false);
                break;

            case 1: // random
                players[p]->setRandom(true);
                break;

            case 2: // sequence
                cin >> file;
                ifs = ifstream{file};
                if (!ifs.good())
                {
                    throw file_not_found(file);
                }
                if (ifs.is_open())
                {
                    string newCmd;
                    while (ifs >> newCmd)
                    {
                        if (ifs.fail())
                        {
                            ifs.clear();
                            ifs.ignore();
                            continue;
                        }
                        cout << newCmd << endl;
                        commands.emplace_back(newCmd);
                        len++;
                    }
                }
                break;
            case 3: // restart
                turn = 0;
                players[0] = make_unique<Player>(seqs[0], seed, startLvl);
                players[1] = make_unique<Player>(seqs[1], seed, startLvl);
                return;
            default: // player cmds
                try {
                    players[p]->playTurn(interpreter->playerCmd(command));
                }
                catch (invalid_move& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            notifyObservers();
            
        }
    }
    int totalCleared = players[p]->getCleared() - numRows;
    int numEffects = totalCleared / 2;

    while (numEffects)
    {
        cout << "Effect available" << endl;
        cout << "Select an effect : blind / heavy / force" << endl;
        cin >> input;
        if (input == "blind" || input == "heavy")
        {
            players[p + 1 % 2]->setEffect(input);
        }
        else if (input == "force")
        {
            cout << "Enter a block: " << endl; 
            char c;
            while (cin >> c) {
                char blockC = toUpper(c);
                if (blockC == 'S' || blockC == 'Z' || blockC == 'I' || blockC == 'O' || blockC == 'T' || blockC == 'L' || blockC == 'J') {
                    int next = turn + 1 % 2;
                    players[next]->setForcedChar(c);
                    players[next]->setEffect(input);
                    break;
                } else {
                    cout << "Invalid block. Enter new block: " << endl;
                }
            }
        }
        numEffects--;
    }
    int currScore = players[p]->getScore();
    if (currScore > highscore)
    {
        highscore = currScore;
        cout << "New Highscore!" << endl;
    }
    players[p]->resetEffects();
    try
    {
        players[p]->setup();
    }
    catch (game_over &e)
    {
        isFinished = true;
        return;
    }
    turn++;
}
