#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include "commands.h"
#include "../common/exceptions.h"

using namespace std;

struct Commands::CommandsImpl
{
    // needs to contain 3 maps, game, player, interpreter commands
    static map<string, int> gameCommands;
    static map<string, int> playerCommands;
    static map<string, int> interpreterCommands;

    static map<string, string> prefixMap; // maps prefixes to fullnames

    static vector<string> singleCalls; // list of single call commands

    bool useMacros;
    map<string, vector<string>> macros;

    CommandsImpl(bool useMacros) noexcept;
    ~CommandsImpl() noexcept = default;

    // internal tools
    void makePrefixes(string &command, bool remake=false); // remaps the commands to their newest shortest prefixes after adding command
    string stringInterpret(string &command);

    // interface implementations
    vector<string> interpret(string &command, bool useMacros);
    bool rename(string &existing, string &newName);
    bool addMacro(string &command);
};

// command maps
map<string, int> Commands::CommandsImpl::gameCommands =
    {{"norandom", 0},
     {"random", 1},
     {"sequence", 2},
     {"restart", 3},
     {"blind", 4},
     {"heavy", 5},
     {"force", 6}};

map<string, int> Commands::CommandsImpl::playerCommands =
    {{"left", 0},
     {"right", 1},
     {"down", 2},
     {"clockwise", 3},
     {"counterclockwise", 4},
     {"drop", 5},
     {"levelup", 6},
     {"leveldown", 7},
     {"I", 8},
     {"J", 9},
     {"L", 10},
     {"O", 11},
     {"S", 12},
     {"Z", 13},
     {"T", 14}
     };


map<string, int> Commands::CommandsImpl::interpreterCommands =
    {{"macro", 0},
     {"rename", 1}};

// prefix maps
map<string, string> Commands::CommandsImpl::prefixMap =
    {{"lef", "left"},
     {"ri", "right"},
     {"do", "down"},
     {"cl", "clockwise"},
     {"co", "counterclockwise"},
     {"dr", "drop"},
     {"levelu", "levelup"},
     {"leveld", "leveldown"},
     {"nor", "norandom"},
     {"ra", "random"},
     {"s", "sequence"},
     {"I", "I"},
     {"J", "J"},
     {"L", "L"},
     {"O", "O"},
     {"S", "S"},
     {"Z", "Z"},
     {"T", "T"},
     {"re", "restart"},
     {"b", "blind"},
     {"h", "heavy"},
     {"f", "force"}};

vector<string> Commands::CommandsImpl::singleCalls =  {"restart", "hint", "norandom", "random"};

// flag is modified based on command-line arguments
Commands::CommandsImpl::CommandsImpl(bool useMacros) noexcept : useMacros{useMacros}
{
    if (useMacros)
    {
        for (auto pair : interpreterCommands)
        {
            string command = pair.first;
            makePrefixes(command);
        }
    }
}

// returns the shortest unique prefix of s1 to s2
string uniquePrefix(string &s1, string &s2)
{
    int i = 0;
    int len = s1.size();
    while (s1[i] == s2[i]) i++;
    if (i == len) return s1;
    return s1.substr(0, i + 1);
}

void Commands::CommandsImpl::makePrefixes(string &command, bool remake)
{
    vector<string> toCheck;
    if (remake)
    {
        for (auto pair : prefixMap)
        {
            toCheck.emplace_back(pair.second);
        }
    }
    else
    {
        // check command against current prefixes for first letter
        for (auto it = prefixMap.cbegin(), next_it = it; it != prefixMap.cend(); it = next_it)
        {
            ++next_it;
            // if first letters match, delete existing key and add to list
            if (it->first[0] == command[0])
            {
                toCheck.emplace_back(it->second);
                prefixMap.erase(it);
            }
        }
    }

    toCheck.emplace_back(command);

    // if no characters are shared
    if (toCheck.size() == 1)
    {
        prefixMap[command.substr(0, 1)] = command;
        return;
    }

    // sort the list lexicographically
    sort(toCheck.begin(), toCheck.end());

    int len = toCheck.size();

    prefixMap[uniquePrefix(toCheck[0], toCheck[1])] = toCheck[0]; // first element only needs to be forward checked
    for (int i = 1; i < len - 1; i++)
    {
        // check for the longer minimum prefix
        string forwardsDiff = uniquePrefix(toCheck[i], toCheck[i + 1]);
        string backwardsDiff = uniquePrefix(toCheck[i], toCheck[i - 1]);
        string prefix = (forwardsDiff.size() > backwardsDiff.size()) ? forwardsDiff : backwardsDiff;
        prefixMap[prefix] = toCheck[i];
    }
    prefixMap[uniquePrefix(toCheck[len - 1], toCheck[len - 2])] = toCheck[len - 1]; // last element only needs to be backwards checked
}

// returns if s1 is a substring of s2
bool isSubstring(string &s1, string &s2)
{
    return (s2.find(s1) != string::npos);
}

string Commands::CommandsImpl::stringInterpret(string &command)
{
    string cmd;
    for (char c : command)
    {
        cmd += c;
        auto it = prefixMap.find(cmd);
        if (it != prefixMap.end())
        {
            if (isSubstring(command, it->second))
            {
                return it->second;
            }
        }
    }
    throw command_not_found{command};
}

vector<string> Commands::CommandsImpl::interpret(string &command, bool useMacros)
{
    vector<string> commands;
    int repeats = 1;
    string intParse;
    string cmd;
    for (char c : command)
    {
        if (!isdigit(c)) 
        {
            cmd += c;
        }
        intParse += c;
    }
    istringstream iss{intParse};
    iss >> repeats;
    repeats = (repeats == 0) ? 1 : repeats;
    try
    {
        cmd = stringInterpret(cmd);
    }
    catch(command_not_found& e)
    {
        cerr << e.what() << endl;
        return vector<string>();
    }
    
    if (useMacros)
    {
        auto it = macros.find(command);
        if (it != macros.end())
        {
            return it->second;
        }
    }

    // handles single call commands
    for (string singleUse : singleCalls)
    {
        if (cmd == singleUse)
        {
            repeats = 1;
            break;
        }
    }
    for (int i = 0; i < repeats; i++)
    {
        commands.emplace_back(cmd);
    }
    return commands;
}

// returns true if successful, false otherwise
bool Commands::CommandsImpl::rename(string &existing, string &newName)
{
    if (existing == "macro" || existing == "rename") return false;
    string cmd;
    try
    {
        cmd = stringInterpret(existing);
    }
    catch(command_not_found& e)
    {
        return false;
    }
    for (auto it = prefixMap.cbegin(), next_it = it; it != prefixMap.cend(); it = next_it)
    {
        ++next_it;
        // remove the existing key
        if (it->second == cmd) 
        {
            prefixMap.erase(it);
        }
    }
    // check if the renamed function was a game command 
    auto it = gameCommands.find(cmd);
    if (it != gameCommands.end())
    {
        gameCommands[newName] = it->second;
        gameCommands.erase(it);
    }
    // check if it was a player command
    it = playerCommands.find(cmd);
    if (it != playerCommands.end())
    {
        playerCommands[newName] = it->second;
        playerCommands.erase(it);
    }
    // update prefix map
    makePrefixes(newName, true);
    return true;
}

// returns true if successful, false otherwise
bool Commands::CommandsImpl::addMacro(string &command)
{
    // if the macro name already exists
    if (interpret(command, useMacros).size() != 0) return false;
    if (macros.count(command) != 0) return false;

    // read in commands to be expanded by macro
    string input;
    vector<string> commands;
    while (cin >> input && input != "done")
    {
        if (cin.fail())
        {
            cin.ignore();
            cin.clear();
        }
        vector<string> cmds = interpret(input, useMacros);
        for (string cmd : cmds)
        {
            commands.emplace_back();
        }
    }
    macros[command] = commands;
    makePrefixes(command);
    return true;
}

// constructor declares the impl
Commands::Commands(bool useMacros) noexcept : impl{make_unique<Commands::CommandsImpl>(useMacros)} {}

Commands::~Commands() noexcept = default;

vector<string> Commands::interpret(string &command) { return impl->interpret(command, impl->useMacros); }

bool Commands::rename(string &existing, string &newName) { return impl->rename(existing, newName); }

bool Commands::addMacro(string &command) { return impl->addMacro(command); }

int Commands::gameCmd(std::string & command)
{
    auto it = impl->gameCommands.find(command);
    if (it != impl->gameCommands.end())
    {
        return it->second;
    }
    return -1;
}

int Commands::playerCmd(std::string & command)
{
    auto it = impl->playerCommands.find(command);
    if (it != impl->playerCommands.end())
    {
        return it->second;
    }
    return -1;
}
