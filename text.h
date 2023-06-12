#ifndef _TEXT_
#define _TEXT_

#include <memory>
#include <vector>
#include "observer.h"
#include "player.h"
#include "game.h"

class Text : public Observer
{
    std::shared_ptr<Game> game;
    std::vector<std::shared_ptr<Player>> players;
public:
    Text(std::shared_ptr<Game> game);
    ~Text();
    void notify() override;
};

#endif
