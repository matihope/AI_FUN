//
// Created by mateusz on 9/20/23.
//

#ifndef AI_FUN_SRC_SCENES_READER_HPP_
#define AI_FUN_SRC_SCENES_READER_HPP_

#include <queue>
#include <string>
#include <vector>


using uint = unsigned int;
using byte = u_int8_t;

namespace idx {
	struct Image {
		std::string                    label;
		std::vector<std::vector<byte>> pixels;
	};

	class Reader {
	public:
		Reader(std::string imagesPath, std::string labelsPath);
		[[nodiscard]] const std::vector<Image> &getImages() const;

	private:
		std::string        imagesPath, labelsPath;
		std::vector<Image> images{};

		void                                        readData();
		std::vector<std::vector<std::vector<byte>>> readImageData();
		std::vector<std::string>                    readLabelsData();

		static std::vector<byte> readBytes(const std::string &filePath);
		static uint              readInt(const std::vector<byte> &bytes, uint start);
	};
}  // namespace idx

#endif  // AI_FUN_SRC_SCENES_READER_HPP_
