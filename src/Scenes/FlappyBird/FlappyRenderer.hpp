//
// Created by mateusz on 10/1/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYRENDERER_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYRENDERER_HPP_

#include "FlappyGame.hpp"
#include "WorldEntity/BoxyWorldEntity.hpp"
#include "WorldEntity/WorldEntity.hpp"

#include <queue>

class FlappyRenderer: public mk::WorldEntity {
public:
	FlappyRenderer(FlappyGame *game, mk::Math::Vector2f gameSize);

	void gameUpdate(float dt);
	void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	FlappyGame *game;

	sf::Sprite  playerSprite;
	sf::IntRect playerRect;

	sf::Sprite barTop, barBottom;

	mk::Math::Vector2f gameSize;

	sf::Sprite         background1, background2;
	const sf::Texture *playerTexture;
	const sf::Texture *backgroundTexture;
	const sf::Texture *barTexture;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYRENDERER_HPP_
