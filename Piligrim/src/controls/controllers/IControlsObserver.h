#pragma once

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