#pragma once

#include <vector>


#include "../events/KeyRole.h"
#include "../events/ControlAction.h"
#include "../events/ControlsTable.h"
#include "../Config.h"

#include "IControlsObserver.h"

namespace piligrim {
	namespace controls {
		class Controller
		{
		public:
			void addEventObserver(IControlsObserver* observer);

			void setConfig(const Config& config);

			bool isKeyActive(KeyRole key) const;

			void update(double deltaTime);
		private:
			std::vector<IControlsObserver*> eventObservers_;
			Config config_;
			ControlsTable controlsTable_;

			friend class Window;
		};

	}
}