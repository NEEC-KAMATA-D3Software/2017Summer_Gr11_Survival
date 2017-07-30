#pragma once
#ifndef _BLUECIRQUEEFFECT_H_
#define _BLUECIRQUEEFFECT_H_

#include "GameObject.h"

class BlueCirqueEffect : public GameObject {
public:
	BlueCirqueEffect();

	virtual void update() override;
	virtual void initialize() override;
	virtual void drawBody() override;
	virtual void drawShadow() override;
	virtual void drawDebug() override;

protected:
	virtual void checkCollitionData() override;
};

#endif // !_BLUECIRQUEEFFECT_H_
