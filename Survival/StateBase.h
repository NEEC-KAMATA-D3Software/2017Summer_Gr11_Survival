#pragma once
#ifndef _STATEBASE_H_
#define _STATEBASE_H_

#include <memory>

enum class eTrans {
	TOTHIS,
	TONEXT,
};

class ObjectManager;

template<class T>
class StateBase {
public:
	StateBase(): isInitialize(true) {}

	std::shared_ptr<StateBase<T>> update(T& thisState) {
		if (isInitialize) {
			initialize(thisState);
			isInitialize = false;
		}
		std::shared_ptr<StateBase<T>> nextState;
		eTrans trans = action(thisState, nextState);

		if (trans == eTrans::TONEXT) {
			exitAction(thisState);
		}
		return nextState;
	}

	virtual void draw() {}
	virtual void drawDebug() {}

protected:
	virtual void initialize(T& thisState) {};
	virtual eTrans action(T& thisState, std::shared_ptr<StateBase<T>>& nextState) {
		return eTrans::TOTHIS;
	}
	virtual void exitAction(T& thisState) {};

private:
	bool isInitialize;
};


#endif // !_STATEBASE_H_

