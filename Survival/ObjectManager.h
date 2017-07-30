#pragma once
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <list>
#include <memory>

class GameObject;

using ObjectListItr = std::list<std::shared_ptr<GameObject>>::iterator;
using ObjectList = std::list<std::shared_ptr<GameObject>>;
using ObjectPtr = std::shared_ptr<GameObject>;

class ObjectManager {
public:
	ObjectManager();
	~ObjectManager();

	void addObject(ObjectPtr object);
	void clearObjects();
	void initialize();
	void update();
	int getPlayerCount();
	int getPlayerID();
	void drawBody(int x, int y, int h);
	void drawShadow(int x, int y, int h);
	void drawDebug();

private:
	bool isCollitionAble(ObjectPtr object1, ObjectPtr object2);

private:
	ObjectList m_ObjectPtrs;
};

#endif // !_OBJECTMANAGER_H_
