#ifndef _COMMANDS_
#define _COMMANDS_

#include <string>
#include <memory>
#include "player.h"

class Commands final
{
    class CommandsImpl;
    std::unique_ptr<CommandsImpl> impl;

public:
    Commands(bool useMacros=false) noexcept;
    ~Commands() noexcept;

    // get the vec, iterate through, calling gameCmd, else playerCmd
    // requires a check for macro and rename
    std::vector<std::string> interpret(std::string &command); // interprets a string input and applies commands appropriately
    
    int gameCmd(std::string &command); // interprets a game command
    int playerCmd(std::string &command); // interprets a player's move

    bool rename(std::string &existing, std::string &newName); // renames a command
    bool addMacro(std::string &command);                      // adds a macro
};

#endif
