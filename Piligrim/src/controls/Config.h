#pragma once

#include <string>

#include "events/KeyRole.h"

namespace piligrim {
	namespace controls {

		class Config
		{
		public:
			Config();
			int getKeyCode(KeyRole key) const;
			void load(std::string path);

		private:
			int bindings_[KeyRole::MaxKeyRole];
		};

	}
}