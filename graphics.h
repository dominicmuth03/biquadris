#ifndef _GRAPHICS_
#define _GRAPHICS_

#include <memory>
#include <vector>
#include "observer.h"
#include "window.h"
#include "game.h"
#include "player.h"
#include "game.h"
#include <map>

class Graphics : public Observer
{
    std::shared_ptr<Game> game;
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::vector<char>> oldStates;
    std::vector<std::vector<char>> newStates;
    std::map<int,char> getDeltas(int p);
    std::unique_ptr<Xwindow> xWindow;
   // Xwindow * xWindow;

    void segmentedBlockPrinter(char c1, char c2);
    void initBackground();
public:
    Graphics(std::shared_ptr<Game> game);
    ~Graphics();
    void notify() override;
};
#endif