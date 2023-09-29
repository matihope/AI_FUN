

#include "IdxDigitTrainer.hpp"

int main() {
	IdxDigitTrainer::teachImagesAugmented("models/digits/digitsUltimate.json");
	IdxDigitTrainer::testImages("models/digits/digitsUltimate.json");
}
