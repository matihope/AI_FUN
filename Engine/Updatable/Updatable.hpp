#pragma once
#include <memory>

namespace mk {
	class Updatable {
	public:
		virtual void update(const float dt){};
		virtual void physicsUpdate(const float dt){};
		virtual void ready(){};
	};
}  // namespace mk
