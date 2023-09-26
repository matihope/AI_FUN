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

	static idx::Image  randomShift(idx::Image image, double backgroundColor);
	static sf::IntRect getBounds(const idx::Image &image, double backgroundColor);

	// times > 0 -> right, down,
	// times < 0 -> left, up.
	static idx::Image shiftHorizontal(idx::Image image, double backgroundColor, int times);
	static idx::Image shiftVertical(idx::Image image, double backgroundColor, int times);

private:
	void handleEvent(const sf::Event &event) override;

	static idx::Image shiftLeft(idx::Image image, double backgroundColor);
	static idx::Image shiftLeft(idx::Image image, double backgroundColor, int times);
	static idx::Image shiftRight(idx::Image image, double backgroundColor, int times);
	static idx::Image shiftRight(idx::Image image, double backgroundColor);
	static idx::Image shiftUp(idx::Image image, double backgroundColor);
	static idx::Image shiftUp(idx::Image image, double backgroundColor, int times);
	static idx::Image shiftDown(idx::Image image, double backgroundColor, int times);
	static idx::Image shiftDown(idx::Image image, double backgroundColor);


	IdxImageViewer *viewer;
	idx::Reader     reader;
};


#endif  // AI_FUN_SRC_SCENES_IDXTESTIMGRECOGNITION_TESTIMAGETRANSITIONS_HPP_
