#include "Controller.h"

#include <GLFW/glfw3.h>

#include "../../utils/logs.h"



void  Controller::addEventObserver(IControlsObserver* observer)
{
	eventObservers_.push_back(observer);
}



void Controller::setConfig(const Config& config)
{
	config_ = config;
}



bool Controller::isKeyActive(KeyRole key) const
{
	return controlsTable_.keyStates[config_.getKeyCode(key)] != GLFW_RELEASE;
}



vec2 Controller::getMousePosition() const
{
	return controlsTable_.mousePosition;
}



vec2 Controller::getMouseDelta() const
{
	return controlsTable_.deltaMove;
}



void Controller::update(double deltaTime)
{
	for (auto observer : eventObservers_) {
		observer->onControllerEvent(this, deltaTime);
	}
	controlsTable_.deltaMove.x = 0;
	controlsTable_.deltaMove.y = 0;
}