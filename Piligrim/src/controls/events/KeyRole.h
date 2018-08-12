#pragma once

namespace piligrim {
	namespace controls {

		enum KeyRole : __int8
		{
			Nothing,
			Forward,
			Back,
			Up,
			Down,
			Right,
			Left,

			Escape,
			CursorMove,
			Center,
			Print,

			MaxKeyRole
		};
	}
}