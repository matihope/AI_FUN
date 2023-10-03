//
// Created by mateusz on 9/20/23.
//

#include "Reader.hpp"

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <iterator>
#include <utility>

namespace idx {
	idx::Reader::Reader(std::string imagesPath, std::string labelsPath):
		  imagesPath(std::move(imagesPath)),
		  labelsPath(std::move(labelsPath)) {
		readData();
	}

	const std::vector<Image> &idx::Reader::getImages() const { return images; }

	void Reader::readData() {
		auto imagesData = readImageData();
		auto labels     = readLabelsData();

		images.clear();
		for (int i = 0; i < imagesData.size(); i++)
			images.emplace_back(labels[i], imagesData[i]);
	}

	std::vector<std::vector<std::vector<byte>>> Reader::readImageData() {
		auto bytes = readBytes(imagesPath);

		[[maybe_unused]] uint magicNumber    = readInt(bytes, 4 * 0);
		uint                  numberOfImages = readInt(bytes, 4 * 1);
		uint                  numberOfRows   = readInt(bytes, 4 * 2);
		uint                  numberOfCols   = readInt(bytes, 4 * 3);


		std::vector<std::vector<std::vector<byte>>> newImages;
		uint                                        dataIndex = 16;
		for (uint imageIndex = 0; imageIndex < numberOfImages; imageIndex++) {
			std::vector<std::vector<byte>> image;
			for (uint rowIndex = 0; rowIndex < numberOfRows; rowIndex++) {
				std::vector<byte> row;
				for (uint colIndex = 0; colIndex < numberOfCols; colIndex++)
					row.push_back(bytes[dataIndex++]);
				image.push_back(std::move(row));
			}
			newImages.push_back(std::move(image));
		}

		for (const auto &img : newImages) {
			if (img.size() != 28) std::cerr << "wrong!\n";
			for (const auto &row : img)
				if (row.size() != 28) std::cerr << "wrong2!\n";
		}

		return newImages;
	}

	std::vector<std::string> Reader::readLabelsData() {
		auto                     bytes = readBytes(labelsPath);
		std::vector<std::string> labels;

		[[maybe_unused]] uint magicNumber    = readInt(bytes, 4 * 0);
		uint                  numberOfLabels = readInt(bytes, 4 * 1);

		uint index = 4 * 2;
		for (uint labelIndex = 0; labelIndex < numberOfLabels; ++labelIndex) {
			byte label = bytes[index++];
			labels.emplace_back(std::to_string(label));
		}

		return labels;
	}

	std::vector<byte> Reader::readBytes(const std::string &filePath) {
		std::vector<byte> bytes;

		//		std::ifstream file(filePath);
		//
		//		if (!file.is_open()) {
		//			std::cerr << "File does not exist! : " << filePath << "\n";
		//			return {};
		//		}
		//
		//		while (!file.eof()) {
		//			char b;
		//			file.get(b);
		//			bytes.push_back((byte) b);
		//		}
		//
		//		file.close();

		// open file
		std::ifstream file(filePath, std::ios::binary);

		// stop eating newlines in binary mode
		file.unsetf(std::ios::skipws);

		// get file length
		file.seekg(0, std::ios::end);
		auto length = file.tellg();
		file.seekg(0, std::ios::beg);

		bytes.insert(
			bytes.begin(),
			std::istream_iterator<byte>(file),
			std::istream_iterator<byte>()
		);

		file.close();

		return bytes;
	}

	uint pow(uint number, uint power) {
		uint result = 1;
		while (power) {
			if (power & 1) result *= number;
			number *= number;
			power /= 2;
		}
		return result;
	}

	uint Reader::readInt(const std::vector<byte> &bytes, uint start) {
		uint result = 0;
		for (uint byteOffset = 0; byteOffset < 4; byteOffset++)
			result += pow(256, 3 - byteOffset) * bytes[start + byteOffset];
		return result;
	}

	void Reader::setImage(uint index, const Image &image) {
		images[index] = image;
	}
}  // namespace idx
