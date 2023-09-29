//
// Created by mateusz on 9/26/23.
//

#ifndef AI_FUN_SRC_SCENES_IDXTESTIMGRECOGNITION_TESTIMAGETRANSITIONS_HPP_
#define AI_FUN_SRC_SCENES_IDXTESTIMGRECOGNITION_TESTIMAGETRANSITIONS_HPP_

#include "IdxImageViewer.hpp"
#include "WorldEntity/WorldEntity.hpp"

class TestImageTransitions: public mk::WorldEntity {
public:
	TestImageTransitions();

	static idx::Image  randomShift(idx::Image image, int backgroundColor, int drawColor);
	static sf::IntRect getBounds(const idx::Image &image, int backgroundColor);

	// times > 0 -> right, down,
	// times < 0 -> left, up.
	static idx::Image shiftHorizontal(idx::Image image, int backgroundColor, int times);
	static idx::Image shiftVertical(idx::Image image, int backgroundColor, int times);
	static idx::Image addNoise(idx::Image image, int backgroundColor, int drawColor, int percentChance);

private:
	void handleEvent(const sf::Event &event) override;

	static idx::Image shiftLeft(idx::Image image, int backgroundColor);
	static idx::Image shiftLeft(idx::Image image, int backgroundColor, int times);
	static idx::Image shiftRight(idx::Image image, int backgroundColor, int times);
	static idx::Image shiftRight(idx::Image image, int backgroundColor);
	static idx::Image shiftUp(idx::Image image, int backgroundColor);
	static idx::Image shiftUp(idx::Image image, int backgroundColor, int times);
	static idx::Image shiftDown(idx::Image image, int backgroundColor, int times);
	static idx::Image shiftDown(idx::Image image, int backgroundColor);


	IdxImageViewer   *viewer;
	idx::Reader       readerOriginal, reader2;
	static idx::Image addRotationAndScale(idx::Image image, int color, int i);
};


#endif  // AI_FUN_SRC_SCENES_IDXTESTIMGRECOGNITION_TESTIMAGETRANSITIONS_HPP_
