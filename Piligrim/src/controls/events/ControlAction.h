#pragma once

namespace piligrim {
	namespace controls {

		enum ControlAction : __int8
		{
			NOTHING    = 1 << 1,

			PRESS      = 1 << 2,
			REPEAT     = 1 << 3,
			RELEASE    = 1 << 4,

			MOUSE_MOVE = 1 << 5,
		};
		
	}
}