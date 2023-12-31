//
// Created by mateusz on 9/25/23.
//

#ifndef AI_FUN_SRC_SCENES_MAINMENU_HPP_
#define AI_FUN_SRC_SCENES_MAINMENU_HPP_

#include "GUI/Button.hpp"
#include "WorldEntity/WorldEntity.hpp"

class MainMenu: public mk::WorldEntity {
public:
	MainMenu();

private:
	void onUpdate(float dt) override;

	mk::GUI::Button *recognize, *draw, *playFlappy;
};


#endif  // AI_FUN_SRC_SCENES_MAINMENU_HPP_
