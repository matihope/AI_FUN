//
// Created by mateusz on 9/20/23.
//

#ifndef AI_FUN_SRC_SCENES_IMAGES_HPP_
#define AI_FUN_SRC_SCENES_IMAGES_HPP_

#include "MNISTImageViewer.hpp"
#include "WorldEntity/WorldEntity.hpp"

class Images: public WorldEntity {
public:
	Images();

private:
	idx::Reader                   reader;
	std::vector<MNISTImageViewer> viewers;
};


#endif  // AI_FUN_SRC_SCENES_IMAGES_HPP_
