#include <memory>
#include <vector>
#include <iostream>
#include <map>
#include "text.h"
#include "player.h"
#include "board.h"

using namespace std;
const int width = 11;
const int height = 18;

void divider() {//prints a divider
    cout << "      ";
}

void pagebreak() { //prints the bottom line of the two biquadris boards
    for (int x = 0; x < width; x++) {
        cout << "-";
    }
    divider();
    for (int x = 0; x < width; x++) {
        cout << "-";
    }
    cout <<endl;
}


void segmentedBlockPrinter(char c, int row) { //twobyfourprinter
    map<char, string> zero =  {{'I', "I "}, {'J'," J"}, {'L',"L "}, {'O',"OO"}, {'S',"S "},{'Z'," Z"}, {'T',"T "}};
    map<char, string> one =   {{'I', "I "}, {'J'," J"}, {'L',"L "}, {'O',"OO"}, {'S',"SS"},{'Z',"ZZ"}, {'T',"TT"}};
    map<char, string> two =   {{'I', "I "}, {'J',"JJ"}, {'L',"LL"}, {'O',"  "}, {'S'," S"},{'Z',"Z "}, {'T',"T "}};
    map<char, string> three = {{'I', "I "}, {'J',"  "}, {'L',"  "}, {'O',"  "}, {'S',"  "},{'Z',"  "}, {'T',"  "}};
    vector<map<char, string>> blockRow = {zero, one, two, three};
    cout <<blockRow[row][c] << "         ";
}

Text::~Text() {
    game->detach(this);
};

void Text::notify() {

    shared_ptr<Player> p1 = players[0];//shit to get the boardstate
    shared_ptr<Player> p2 = players[1];//shit to get the boardstate
    vector<char> b1 = p1->getState();
    vector<char> b2 = p2->getState();

    //print p1 level
    cout << "Level:    " << p1->getLevel();
    divider();
    //print p2 level
    cout << "Level:    " << p2->getLevel();
    cout << endl; 

    //print p1 score
    cout <<"Score:    " << p1->getScore();
    divider();
    //print p2 score
    cout <<"Score:    " << p2->getScore();
    cout <<  endl; 
    
    //print pagebreak at top
    pagebreak();

    //print both board states
    for (int y = 3; y < height; y++) {

        for (int x = 0; x < width; x++){
            cout<< b1[y*width + x];
        }
        divider();
        for (int x = 0; x < width; x++){
            cout<< b2[y*width + x];
        }
        cout << endl;
    }

    //print pagebreak at top;
    pagebreak();

    cout << "Next:     ";
    divider();
    cout << "Next:     " << endl;
    //create a function that uses p1->getNextBlockChar(), and prints the block on a 2x4
    char p1Next = p1->getNext();
    char p2Next = p2->getNext();
    for (int i = 0; i < 4; i++) {
        segmentedBlockPrinter(p1Next, i);
        divider();
        segmentedBlockPrinter(p2Next, i);
        cout << endl;
    }
}

Text::Text(std::shared_ptr<Game> game) : game{game} {
    players.emplace_back(game->getPlayers()[0]);
    players.emplace_back(game->getPlayers()[1]);
    game->attach(this);
};
