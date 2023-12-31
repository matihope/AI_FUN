//
// Created by mateusz on 9/25/23.
//

#ifndef AI_FUN_SRC_SCENES_DIGITDRAWING_DRAWBOARD_HPP_
#define AI_FUN_SRC_SCENES_DIGITDRAWING_DRAWBOARD_HPP_

#include "Base/NeuralNetwork.hpp"
#include "GUI/Button.hpp"
#include "GUI/Label.hpp"
#include "SpriteBatch/SpriteBatch.hpp"
#include "WorldEntity/WorldEntity.hpp"

#include <Math/Math.hpp>

class DrawBoard: public mk::WorldEntity {
public:
	explicit DrawBoard(uint boardSizePixels = 28);
	const std::vector<double> &getBoardAsData() const;

private:
	void onUpdate(float dt) override;

	mk::Math::Vector2i lastMousePos{ -1, -1 };
	bool               hasDrawnLastUpdate{};

	mk::SpriteBatch *batch;
	uint             boardSize;
	mk::GUI::Label  *aiAnswer;
	mk::GUI::Label  *aiOther;
	mk::GUI::Button *resetBoard;

	std::vector<double> boardData;

	std::unique_ptr<ai::NeuralNetwork> network;
};


#endif  // AI_FUN_SRC_SCENES_DIGITDRAWING_DRAWBOARD_HPP_
