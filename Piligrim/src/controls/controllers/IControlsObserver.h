#pragma once

class Controller;
class IControlsObserver
{
public:
	virtual void onControllerEvent(Controller*, double) = 0;
};