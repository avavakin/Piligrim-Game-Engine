#include "Config.h"

#include <GLFW/glfw3.h>
namespace piligrim{
	namespace controls {



		Config::Config()
		{

			bindings_[KeyRole::Escape] = GLFW_KEY_ESCAPE;

			bindings_[KeyRole::Up] = GLFW_KEY_SPACE;
			bindings_[KeyRole::Down] = GLFW_KEY_LEFT_SHIFT;

			bindings_[KeyRole::Forward] = GLFW_KEY_W;
			bindings_[KeyRole::Left] = GLFW_KEY_A;
			bindings_[KeyRole::Back] = GLFW_KEY_S;
			bindings_[KeyRole::Right]  = GLFW_KEY_D;

			bindings_[KeyRole::Print] = GLFW_KEY_P;
			bindings_[KeyRole::Center] = GLFW_KEY_C;
		}



		int Config::getKeyCode(KeyRole key) const
		{
			return bindings_[key];
		}



		void Config::load(std::string path)
		{

			// TODO
		}



	}
}
