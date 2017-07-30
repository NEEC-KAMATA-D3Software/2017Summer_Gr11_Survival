#include "ObjectManager.h"
#include "GameObject.h"
#include "GameConst.h"
#include "Methord.h"

ObjectManager::ObjectManager():
	m_ObjectPtrs()
{}
ObjectManager::~ObjectManager() {
	m_ObjectPtrs.clear();
}

void ObjectManager::addObject(ObjectPtr object) {
	m_ObjectPtrs.push_back(object);
}

void ObjectManager::clearObjects() {
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end();) {
		m_ObjectPtrs.erase(i++);
	}
	m_ObjectPtrs.clear();
}

void ObjectManager::initialize() {
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		(*i)->initialize();
		(*i)->setObjectManager(std::make_shared<ObjectManager>(*this));
	}
}

void ObjectManager::update() {
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		(*i)->update();
		if ((*i)->getProperty().Tag == eTag::NONE) { continue; }
		if ((*i)->getProperty().HP <= 0) { continue; }

		for (ObjectListItr j = m_ObjectPtrs.begin(); j != m_ObjectPtrs.end(); ++j) {
			if (!isCollitionAble((*i), (*j))) { continue; }
			if (Methord::CollitionCircle((*i), (*j))) {
				(*i)->Hit((*j));
				(*j)->Hit((*i));
			}
		}
	}
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end();) {
		if ((*i)->getProperty().IsDead) {
			m_ObjectPtrs.erase(i++);
		}else {
			i++;
		}
	}
}

int ObjectManager::getPlayerCount() {
	int playerCount = 0;
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		if ((*i)->getProperty().Tag == eTag::PLAYER) {
			playerCount++;
		}
	}
	return playerCount;
}

int ObjectManager::getPlayerID() {
	int playerID = 0;
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		if ((*i)->getProperty().Tag == eTag::PLAYER) {
			playerID = (*i)->getProperty().ID;
		}
	}
	return playerID;
}

void ObjectManager::drawBody(int x, int y, int h) {
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		int _X = (int)(*i)->getProperty().CurrentPoint.X;
		int _Y = (int)(*i)->getProperty().CurrentPoint.Y;
		int _H = (*i)->getProperty().CurrentLevel;
		if (x == _X && y == _Y&&h == _H) {
			(*i)->drawBody();
		}
	}
}

void ObjectManager::drawShadow(int x, int y, int h) {
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		int _X = (int)(*i)->getProperty().CurrentPoint.X;
		int _Y = (int)(*i)->getProperty().CurrentPoint.Y;
		int _H = (*i)->getProperty().ShadowLevel;
		if (x == _X && y == _Y&&h == _H) {
			(*i)->drawShadow();
		}
	}
}

void ObjectManager::drawDebug() {
	for (ObjectListItr i = m_ObjectPtrs.begin(); i != m_ObjectPtrs.end(); ++i) {
		(*i)->drawDebug();
	}
}

bool ObjectManager::isCollitionAble(ObjectPtr object1, ObjectPtr object2) {
	if (object2->getProperty().Tag == eTag::NONE) { return false; }
	if (object2->getProperty().HP <= 0) { return false; }

	if (object1->getProperty().Tag == object2->getProperty().Tag) {
		return false;
	}
	if (object1->getProperty().ID == object2->getProperty().ID) {
		return false;
	}
	else {
		if (GameConst::GameMode == eGameMode::MULTIPLAY) {
			return false;
		}
	}
}