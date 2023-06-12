#include "exceptions.h"
#include <string>

using namespace std;

// command_not_found implementation
command_not_found::command_not_found(string &command) : command{command} {}

string command_not_found::what()
{
    return command + " is not a valid command.";
}

// command_already_exists implementation
command_already_exists::command_already_exists(string &command) : command{command} {}

string command_already_exists::what()
{
    return command + " is already an existing command.";
}

//file_not_found implementation

string file_not_found::sequence1 = "biquadris_sequence1.txt";
string file_not_found::sequence2 = "biquadris_sequence2.txt";

file_not_found::file_not_found(string &file) : file{file} {}

string file_not_found::what()
{
    return file + " does not exist.";
}

arg_not_found::arg_not_found(string &arg) : arg{arg} {}

string arg_not_found::what()
{
    return arg + " does not exist.";
}

string file_not_found::getDefault(int type)
{
    return (type == 1) ? sequence1 : sequence2;
}

invalid_level::invalid_level(int level) : level{level} {}

string invalid_level::what()
{
    return "invalid level change, you are already at level: " + level;
}

invalid_move::invalid_move() {}

string invalid_move::what()
{
    return "invalid move.";
}

game_over::game_over() {}

string game_over::what()
{
    return "you've lost.";
}
