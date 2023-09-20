//
// Created by mateusz on 9/19/23.
//

#ifndef AI_FUN_SRC_SCENES_MNISTIMAGEVIEWER_HPP_
#define AI_FUN_SRC_SCENES_MNISTIMAGEVIEWER_HPP_

#include "Scenes/idx/Reader.hpp"
#include "WorldEntity/WorldEntity.hpp"

#include <fstream>

class MNISTImageViewer: public WorldEntity {
public:
	explicit MNISTImageViewer(idx::Reader &data);
	void onDraw(sf::RenderTarget &target,
	            sf::RenderStates  states) const override;
	void onUpdate(float dt) override;
	void setImageIndex(uint newImageId);

private:
	idx::Reader          &data;
	[[maybe_unused]] uint imageId{};
	sf::Texture           texture;
};

#endif  // AI_FUN_SRC_SCENES_MNISTIMAGEVIEWER_HPP_
