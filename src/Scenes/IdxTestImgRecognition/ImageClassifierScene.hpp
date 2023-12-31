//
// Created by mateusz on 9/20/23.
//

#ifndef AI_FUN_SRC_SCENES_IMAGECLASSIFIERSCENE_HPP_
#define AI_FUN_SRC_SCENES_IMAGECLASSIFIERSCENE_HPP_

#include "GUI/GUI.hpp"
#include "IdxImageViewer.hpp"
#include "WorldEntity/WorldEntity.hpp"
#include "ai/Base/NeuralNetwork.hpp"
#include "idx/Reader.hpp"

class ImageClassifierScene: public mk::WorldEntity {
public:
	ImageClassifierScene();

	void testImage(uint imageId);


private:
	void onPhysicsUpdate(float dt) override;

	std::unique_ptr<ai::NeuralNetwork> network;

	idx::Reader      reader;
	IdxImageViewer  *viewer;
	mk::GUI::Label  *realLabel, *aiLabel, *idLabel;
	int              currImg;
	bool             pressed{};
	mk::GUI::Button *prevImageBtn, *nextImageBtn, *randomImageBtn,
		*wrongImageBtn;

	void nextImage();
	void prevImage();
};


#endif  // AI_FUN_SRC_SCENES_IMAGECLASSIFIERSCENE_HPP_
