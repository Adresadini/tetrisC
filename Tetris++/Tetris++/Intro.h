#ifndef STATEINTROSFML_H
#define STATEINTROSFML_H

#include <SFML/Audio/Sound.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "GameState.h"
#include "StateMainMenu.h"
#include "Audio.h"
#include "Texture.h"
#include "InitMenu.h"

class Intro : public GameState {
public:
    explicit Intro(InitMenu& initMenu);
    ~Intro() override;

    std::unique_ptr< GameState > GetNextState() override;
    void Draw() override;
    void HandleInput() override;
    void Update() override;

private:
    InitMenu& m_initMenu;
    sf::Clock m_animationTime;
    sf::Sprite m_logoSprite;

    void StopState() override;
    void CenterLogoOrigin();
    void CenterLogoPosition();
    void CreateLogoSprite();
    void PrepareAnimation();
    void PrepareLogo();
};
#endif