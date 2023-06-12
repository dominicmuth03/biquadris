#include "game.h"
#include "player.h"
#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "exceptions.h"
#include "observer.h"
#include "text.h"
#include "graphics.h"
using namespace std;
/*
bonus flags:
-macro
-decay
-autolevel
-multieffects
*/

int main(int argc, char **argv)
{

    vector<bool> flagStates(5, false);
    string file1 = "biquadris_sequence1.txt";
    string file2 = "biquadris_sequence2.txt";
    int seed = 0;
    int startLvl = 0;
    string argv1;
    string argv2;
    for (int i = 1; i < argc; i++)
    {
        argv1 = argv[i];
        if (argv1 == "-text")
        {
            flagStates[0] = true;
        }
        else if (argv1 == "-seed")
        {
            i++;
            argv2 = argv[i];
            istringstream iss{argv2};
            if (iss >> seed) {
            } else {
                throw arg_not_found(argv2);
            }
        }
        else if (argv1 == "-scriptfile")
        {
            i++;
            file1 = argv2;
        }
        else if (argv1 == "-scriptfile2")
        {
            i++;
            file2 = argv[i];
        }
        else if (argv1 == "-startlevel")
        {
            i++;
            argv2 = argv[i];
            istringstream iss{argv2};
            if (iss >> startLvl) {
            } else {
                throw arg_not_found(argv2);
            }
        } 
        else if (argv1 == "-macro")
        {
            flagStates[1] = true;
        } 
        else if (argv1 == "-decay")
        {
            flagStates[2] = true;
        }
        else if (argv1 == "-autolevel")
        {
            flagStates[3] = true;
        }
        else if (argv1 == "-multieffects")
        {
            flagStates[4] = true;
        }
        else
        {
            string command = argv[i];
            throw command_not_found(command);
        }
    }
    vector<string> files = {file1, file2};
    shared_ptr<Game> biquadris = make_shared<Game>(seed, startLvl, files, flagStates);
    Text textObserver(biquadris);
    if (!flagStates[0]) {
        Graphics graphicsObserver(biquadris);
    }
    biquadris->run();
}
