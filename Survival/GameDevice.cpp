#include "GameDevice.h"
#include "InputState.h"
#include "Controller.h"

GameDevice::GameDevice():
	m_InputStatePtr(new InputState()),
	m_ContrStatePtr(new Controller())
{}

GameDevice::~GameDevice() {}

void GameDevice::initialize() {}

void GameDevice::update() {
	m_InputStatePtr->updateKey();
	m_ContrStatePtr->updateButton();
}

std::shared_ptr<InputState> GameDevice::getInputState() {
	return m_InputStatePtr;
}

std::shared_ptr<Controller> GameDevice::getContrState() {
	return m_ContrStatePtr;
}