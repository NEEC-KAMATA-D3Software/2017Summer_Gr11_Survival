#pragma once
#ifndef _RUPTUREEFFECT_H_
#define _RUPTUREEFFECT_H_

#include "GameObject.h"

class RuptureEffect : public GameObject {
public:
	RuptureEffect();

	virtual void update() override;
	virtual void initialize() override;
	virtual void drawBody() override;
	virtual void drawShadow() override;
	virtual void drawDebug() override;

protected:
	virtual void checkCollitionData() override;

};

#endif // !_RUPTUREEFFECT_H_
