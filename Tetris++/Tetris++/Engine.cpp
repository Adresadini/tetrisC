#include "Engine.h"

Engine::Engine() = default;

Engine::~Engine() 
{
    while (!m_states.empty()) 
    {
        m_states.pop();
    }
}

void Engine::StartGame() 
{
    PushInitialState();
    GameLoop();
}

void Engine::PushInitialState() 
{
    std::unique_ptr< GameState > introState(new Intro(m_initMenu));
    PushState(std::move(introState));
}

void Engine::GameLoop() 
{
    sf::RenderWindow& window = m_initMenu.GetWindow();

    sf::Clock clock;
    while (window.isOpen()) {
        if (!m_states.top()->isStateRunning()) 
        {
            std::unique_ptr< GameState > nextState = m_states.top()->GetNextState();
            ChangeState(std::move(nextState));
        }

        if (!m_initMenu.IsExitGame()) 
        {
            m_states.top()->HandleInput();
            m_states.top()->Update();

            window.clear(sf::Color::Black);
            m_states.top()->Draw();
            window.display();

        }
        else 
        {
            window.close();
        }
    }
}

void Engine::PopState() 
{
    if (!m_states.empty()) 
    {
        m_states.pop();
    }
}

void Engine::PushState(std::unique_ptr< GameState > state) 
{
    m_states.push(std::move(state));
}

void Engine::ChangeState(std::unique_ptr< GameState > state) 
{
    PopState();
    PushState(std::move(state));
}