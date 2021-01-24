#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <stack>

#include <SFML/Graphics/RenderWindow.hpp>

#include "InitMenu.h"
#include "GameState.h"
#include "Intro.h"

class Engine {
public:
    Engine();
    virtual ~Engine();

    void StartGame();

private:
    InitMenu m_initMenu;
    std::stack< std::unique_ptr< GameState > > m_states;

    void ChangeState(std::unique_ptr< GameState > state);
    void GameLoop();
    void PopState();
    void PushInitialState();
    void PushState(std::unique_ptr< GameState > state);
};

#endif