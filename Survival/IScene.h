#pragma once
#ifndef _ISCENE_H_
#define _ISCENE_H_

enum class eScene {
	LOADING,
	TITLE,
	GAMEPLAY,
	YOULOSE,
	YOUWIN,
	NONE,
};

class IScene {
public:
	virtual ~IScene() {}

	virtual void initialize() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void drawDebug() = 0;

	virtual bool isEnd() = 0;
	virtual eScene next() = 0;
};


#endif // !_ISCENE_H_
