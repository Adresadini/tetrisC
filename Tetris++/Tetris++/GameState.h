#pragma once
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <memory>

class GameState {
public:
    GameState() : m_stateRunning(true) {};
    virtual ~GameState() = default;

    bool isStateRunning() 
    { 
        return m_stateRunning; 
    };

    virtual std::unique_ptr< GameState > getNextState() = 0;

protected:
    bool m_stateRunning;
};
#endif