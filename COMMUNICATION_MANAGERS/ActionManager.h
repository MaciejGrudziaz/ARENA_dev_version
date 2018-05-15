#pragma once
#include <Functor.h>
#include <vector>

class ActionManager {
	typedef Functor<void, NullType> functor_;
	std::vector<functor_> actions;

public:

	void AddAction(const functor_& action) {
		actions.push_back(functor_(action));
	}

	void PerformAllActions() {
		for (functor_& action : actions)
			action();

		actions.clear();
	}
};
