//
// Created by mateusz on 9/20/23.
//

#ifndef AI_FUN_SRC_SCENES_IMAGECLASSIFIER_HPP_
#define AI_FUN_SRC_SCENES_IMAGECLASSIFIER_HPP_

#include "WorldEntity/WorldEntity.hpp"
#include "ai/Base/NeuralNetwork.hpp"
#include "idx/Reader.hpp"
#include "idxImageViewer.hpp"

#include <GUI/GUI.hpp>

class ImageClassifier: public WorldEntity {
public:
	ImageClassifier();

	void testImage(uint imageId);

	void onPhysicsUpdate(float dt) override;

private:
	idx::Reader                        reader;
	idxImageViewer                    *viewer;
	GUI::Label                        *realLabel, *aiLabel;
	std::unique_ptr<ai::NeuralNetwork> network;
	uint                               currImg;
	bool                               pressed{};
};


#endif  // AI_FUN_SRC_SCENES_IMAGECLASSIFIER_HPP_
