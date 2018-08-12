#pragma once

#include "../../math/vec2.h"
#include "KeyRole.h"
#include "ControlAction.h"

#define MAX_KEYS_COUNT 1024

namespace piligrim {
	namespace controls {

		struct ControlsTable
		{
			int keyStates[MAX_KEYS_COUNT];
			math::vec2 deltaMove;
			math::vec2 mousePosition;
		};

	}
}