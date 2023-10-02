//
// Created by mateusz on 10/1/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYRENDERER_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYRENDERER_HPP_

#include "FlappyGame.hpp"
#include "WorldEntity/WorldEntity.hpp"

class FlappyRenderer: public mk::WorldEntity {
public:
	explicit FlappyRenderer(FlappyGame *game);

	void onPhysicsUpdate(float dt) override;
	void onDraw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
	FlappyGame *game;

	sf::Texture playerTexture;
	sf::Sprite  playerSprite;

	sf::Sprite barTop, barBottom;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYRENDERER_HPP_
