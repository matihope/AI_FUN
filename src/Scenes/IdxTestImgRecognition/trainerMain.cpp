

#include "IdxDigitTrainer.hpp"

int main() {
	IdxDigitTrainer::teachImagesAugmented("digitsUltimate.json");
	IdxDigitTrainer::testImages("digitsUltimate.json");
}
