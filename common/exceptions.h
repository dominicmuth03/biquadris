#ifndef _EXCEPTIONS_
#define _EXCEPTIONS_

#include <exception>
#include <string>

// EXCEPTIONS CLASS : ADD TO IT AS NEEDED

class command_not_found : public std::exception
{
    std::string command;

public:
    command_not_found(std::string &command);
    std::string what();
};

class command_already_exists : public std::exception
{
    std::string command;

public:
    command_already_exists(std::string &command);
    std::string what();
};

// requires careful definition of sequences
class file_not_found : public std::exception
{
    static std::string sequence1;
    static std::string sequence2;
    std::string file;

public:
    file_not_found(std::string &command);
    std::string what();
    std::string getDefault(int type); // returns the default file for sequence 'type'
};

class arg_not_found : public std::exception
{
    static std::string sequence1;
    static std::string sequence2;
    std::string arg;

public:
    arg_not_found(std::string &arg);
    std::string what();
    std::string getDefault(int type); // returns the default file for sequence 'type'
};

class invalid_level : public std::exception
{
    int level;
public:
    invalid_level(int level);
    std::string what();
};

class invalid_move : public std::exception
{
public:
    invalid_move();
    std::string what();
};

class game_over : public std::exception
{
public:
    game_over();
    std::string what();
};

#endif
