#pragma once
#define GLEW_STATIC
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/logs.h"
#include "../utils/glcall.h"

namespace piligrim { 
	namespace graphics {

#define MAX_KEYS			1024
#define MAX_MOUSE_BUTTONS	32

		class Window
		{
		public:
			Window(const std::string& title, int width, int height);
			~Window();

			void clear() const;
			void update();
			bool closed() const;

			int getWidth() const;
			int getHeight() const;

			static bool isKeyPressed(unsigned short keycode);
			static bool isMouseButtonPressed(unsigned short buttoncode);
			static void getMousePosition(double &x, double&y);

		private:
			std::string title_;
			int width_, height_;
			GLFWwindow* window_;
			bool closed_;

			static bool keys_[MAX_KEYS];
			static bool mouseButtons_[MAX_MOUSE_BUTTONS];
			static double mouseX_, mouseY_;

		private:
			bool init();

			friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
			friend static void window_resize(GLFWwindow * window, int width, int height);
		};
		
	} 
}