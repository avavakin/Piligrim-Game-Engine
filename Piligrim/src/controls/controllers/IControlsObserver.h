#pragma once

#include "../events/ControlsTable.h"

namespace piligrim {
	namespace controls {
		class Controller;
		class IControlsObserver
		{
		public:
			virtual void onControllerEvent(Controller*, double) = 0;
		};

	}
}