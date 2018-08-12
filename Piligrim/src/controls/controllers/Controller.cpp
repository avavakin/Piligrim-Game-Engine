#include "Controller.h"

#include <GLFW/glfw3.h>

#include "../../utils/logs.h"
namespace piligrim {
	namespace controls {



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



		void Controller::update(double deltaTime)
		{
			for (auto observer : eventObservers_) {
				observer->onControllerEvent(this, deltaTime);
			}
		}



	}
}