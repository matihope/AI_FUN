//
// Created by mateusz on 9/24/23.
//

#ifndef AI_FUN_ENGINE_RANDOM_RANDOM_HPP_
#define AI_FUN_ENGINE_RANDOM_RANDOM_HPP_

#include <random>

namespace mk {

	typedef unsigned int uint;

	class Random {
		Random() = default;
		static Random &get();

		std::default_random_engine generator;
		std::random_device         randomDevice;

	public:
		// singleton stuff
		Random(const Random &)         = delete;
		void operator=(const Random &) = delete;

		static void initSeed(uint seed);
		static void initRandom();

		template<class T>
		static T getInt(T start, T end) {
			auto &me = Random::get();
			return std::uniform_int_distribution<T>(start, end)(me.generator);
		}

		template<class T>
		static T getReal(T start, T end) {
			auto &me = Random::get();
			return std::uniform_real_distribution<T>(start, end)(me.generator);
		}

		template<class T>
		static T getNormalDist(T mean, T stddev) {
			auto &me = Random::get();
			return std::normal_distribution<T>(mean, stddev)(me.generator);
		}
	};

}  // namespace mk

#endif  // AI_FUN_ENGINE_RANDOM_RANDOM_HPP_
