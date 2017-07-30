#pragma once
#ifndef _EXPLOSIONEFFECT_H_
#define _EXPLOSIONEFFECT_H_

#include "GameObject.h"

class ExplosionEffect : public GameObject {
public:
	ExplosionEffect();

	virtual void update() override;
	virtual void initialize() override;
	virtual void drawBody() override;
	virtual void drawShadow() override;
	virtual void drawDebug() override;

protected:
	virtual void checkCollitionData() override;
};

#endif // !_EXPLOSIONEFFECT_H_
