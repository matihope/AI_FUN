//
// Created by mateusz on 9/30/23.
//

#ifndef AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYLEVEL_HPP_
#define AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYLEVEL_HPP_

#include "FlappyGame.hpp"
#include "FlappyRenderer.hpp"
#include "WorldEntity/WorldEntity.hpp"

class FlappyLevel: public mk::WorldEntity {
public:
	FlappyLevel();
	~FlappyLevel();

	void onPhysicsUpdate(float dt) override;

private:
	sf::Vector2u initialViewportSize;

	std::unique_ptr<FlappyGame> game;
	FlappyRenderer             *renderer;
};


#endif  // AI_FUN_SRC_SCENES_FLAPPYBIRD_FLAPPYLEVEL_HPP_
