//
// Created by mateusz on 9/19/23.
//

#ifndef AI_FUN_SRC_SCENES_IDXIMAGEVIEWER_HPP_
#define AI_FUN_SRC_SCENES_IDXIMAGEVIEWER_HPP_

#include "Clickable/Clickable.hpp"
#include "WorldEntity/WorldEntity.hpp"
#include "idx/Reader.hpp"

#include <fstream>

class IdxImageViewer: public mk::WorldEntity {
public:
	explicit IdxImageViewer(idx::Reader &data);
	void onDraw(sf::RenderTarget &target, sf::RenderStates states)
		const override;
	void setImageIndex(uint newImageId);

private:
	idx::Reader          &data;
	[[maybe_unused]] uint imageId{};
	sf::Texture           texture;
	sf::Sprite            digitImage;
};

#endif  // AI_FUN_SRC_SCENES_IDXIMAGEVIEWER_HPP_
