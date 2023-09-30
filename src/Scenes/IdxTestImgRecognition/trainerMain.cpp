

#include "IdxDigitTrainer.hpp"

int main() {
	IdxDigitTrainer::teachImagesAugmented("models/digits/digitsUltimateSoftMax.json");
	IdxDigitTrainer::testImages("models/digits/digitsUltimateSoftMax.json");
}
