#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include "graphics.h"
#include "player.h"
#include "board.h"
#include "window.h"

using namespace std;
const int width = 11;
const int height = 18;

void Graphics::segmentedBlockPrinter(char c1, char c2) {
    map<char, string> zero =  {{'I', "I "}, {'J'," J"}, {'L',"L "}, {'O',"OO"}, {'S',"S "},{'Z'," Z"}, {'T',"T "}};
    map<char, string> one =   {{'I', "I "}, {'J'," J"}, {'L',"L "}, {'O',"OO"}, {'S',"SS"},{'Z',"ZZ"}, {'T',"TT"}};
    map<char, string> two =   {{'I', "I "}, {'J',"JJ"}, {'L',"LL"}, {'O',"  "}, {'S'," S"},{'Z',"Z "}, {'T',"T "}};
    map<char, string> three = {{'I', "I "}, {'J',"  "}, {'L',"  "}, {'O',"  "}, {'S',"  "},{'Z',"  "}, {'T',"  "}};
    vector<map<char, string>> blockRow = {zero, one, two, three};
    for (int i = 0; i < 4; i ++) {
        xWindow->drawString(0, height + 6 + i, blockRow[i][c1]);
        xWindow->drawString(width + 6, height + 6 + i, blockRow[i][c1]);
    }
}

//returns a map of index to char, representing all the differences between a player's old boardstate to it's new boardstate.
map<int,char> Graphics::getDeltas(int p) {  // takes int p, 0 for player1, 1 for player2
    map<int,char> deltas;
    for(int i = 0; i < width * height; i++) {
        char curr = newStates[p][i];
        if (curr != oldStates[p][i]) {
            deltas[i] = curr;
        }
    }
    oldStates[p] = newStates[p];
    return deltas;
}

//string color_vals[10]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown"};

map<char,int> blockColour = {
    {'I', 5},   //cyan
    {'J', 4},   //blue
    {'L', 8},   //orange
    {'O', 6},   //yellow
    {'S', 3},   //green
    {'Z', 2},    //red
    {'T', 7} //magenta
};

void Graphics::notify() {
    map<int,char> p1Deltas = getDeltas(0);
    map<int,char> p2Deltas = getDeltas(1);
    int p1Score = players[0]->getScore();
    int p1Lvl = players[0]->getLevel();
    int p2Score = players[1]->getScore();
    int p2Lvl = players[1]->getLevel();
    //update text and next block each time
    xWindow->drawString(0, 0, "Level:");
    xWindow->drawString(width - 1, 0, to_string(p1Lvl));
    xWindow->drawString(width + 6, 0, "Level:");
    xWindow->drawString(width * 2 + 6 - 1, 0, to_string(p2Lvl));

    xWindow->drawString(0, 1, "Score:");
    xWindow->drawString(width - 6, 1, to_string(p1Score));
    xWindow->drawString(width + 6, 1, "Score:");
    xWindow->drawString(width * 2 + 6 - 6, 1, to_string(p2Score));
    //something render deltas
    int x;
    int y;
    for (auto i : p1Deltas) {
        //render i.second at i.first
        x = i.first % width;
        y = (i.first / width) + 3;
        xWindow->fillRectangle(x, y, 1, 1, blockColour[i.second]);
    }
    for (auto i : p2Deltas) {
        //render i.second at i.first
        x = (i.first % width) + width + 6;
        y = (i.first / width) + 3;
        xWindow->fillRectangle(x, y, 1, 1, blockColour[i.second]);
    }
    xWindow->drawString(0, height + 5, "Next:");
    xWindow->drawString(width + 6, height + 5, "Next:");
    segmentedBlockPrinter(players[0]->getNext(), players[1]->getNext());

}

Graphics::Graphics(shared_ptr<Game> game) : game{game} {
    players.emplace_back(game->getPlayers()[0]);
    players.emplace_back(game->getPlayers()[1]);
    newStates = game->getState();
    for(int i = 0; i < width * height; i++) {
        oldStates.emplace_back(vector<char>('~', '~'));
    }
    xWindow = make_unique<Xwindow>();
    initBackground();
}

Graphics::~Graphics() {
    game->detach(this);
};


void Graphics::initBackground()
{
    xWindow->fillRectangle(500, 500, 1, 1, blockColour[0]);
}
