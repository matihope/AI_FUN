//
// Created by mateusz on 9/18/23.
//

#ifndef AI_FUN_SRC_AI_COACHES_LAYERGRADIENT_HPP_
#define AI_FUN_SRC_AI_COACHES_LAYERGRADIENT_HPP_

#include "../Base/Layer.hpp"

#include <vector>

namespace ai {

	using uint = unsigned int;

	class LayerGradient {
	public:
		explicit LayerGradient(Layer &layer);

		std::vector<std::vector<double>> weightGradient;
		std::vector<double>              biasGradient;

		void   apply(double learnRate, double lambda = 0.0005);
		Layer &getLayer();

	private:
		Layer &layer;
	};

}  // namespace ai

#endif  // AI_FUN_SRC_AI_COACHES_LAYERGRADIENT_HPP_
