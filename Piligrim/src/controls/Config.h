#pragma once

#include <string>

#include "../utils/fileutils.h"

#include "data/KeyRole.h"

namespace piligrim {
	namespace controls {

		class Config
		{
		public:
			Config();
			int getKeyCode(KeyRole key) const;
			void load(std::string path);

			static char invalidConfigMessage[];
			
		private:
			int bindings_[KeyRole::MaxKeyRole];

		private:
			KeyRole parseKeyRole(const std::string& word);
			int parseKeyCode(const std::string& word);
		};

	}
}