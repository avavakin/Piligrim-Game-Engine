#include "window.h"

#include <iostream>
namespace piligrim {
	namespace graphics {

		bool Window::keys_[MAX_KEYS];
		bool Window::mouseButtons_[MAX_MOUSE_BUTTONS];
		double Window::mouseX_;
		double Window::mouseY_;

		Window::Window(const std::string& title, int width, int height)
		{
			title_ = title;
			height_ = height;
			width_ = width;

			if (!init()) {
				glfwTerminate();
			}

			for (unsigned short i = 0; i < MAX_KEYS; i++) {
				keys_[i] = false;
			}

			for (unsigned short i = 0; i < MAX_MOUSE_BUTTONS; i++) {
				mouseButtons_[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		void Window::clear() const
		{
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		}

		void Window::update()
		{
			glfwPollEvents();
			glfwSwapBuffers(window_);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(window_) == 1;
		}

		int Window::getWidth() const
		{
			return width_;
		}

		int Window::getHeight() const
		{
			return height_;
		}

		bool Window::isKeyPressed(unsigned short keycode)
		{
			if (keycode >= MAX_KEYS) {
				return false;
			}
			return keys_[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned short buttoncode)
		{
			if (buttoncode >= MAX_MOUSE_BUTTONS) {
				return false;
			}
			return mouseButtons_[buttoncode];
		}

		void Window::getMousePosition(double & x, double & y)
		{
			x = mouseX_;
			y = mouseY_;
		}

		bool Window::init()
		{
			if (!glfwInit()) {
				LOG_ER("Oh shiit GLFW is NOT OK");
				return false;
			}

			window_ = glfwCreateWindow(width_, height_, title_.c_str(), NULL, NULL);
			if (!window_) {
				glfwTerminate();
				LOG_ER("Failed to create window!");
				return false;
			}

			glfwMakeContextCurrent(window_);
			glfwSetWindowUserPointer(window_, this);
			glfwSetWindowSizeCallback(window_, window_resize);
			glfwSetKeyCallback(window_, key_callback);
			glfwSetMouseButtonCallback(window_, mouse_button_callback);
			glfwSetCursorPosCallback(window_, cursor_position_callback);
			
			if (glewInit() != GLEW_OK) {
				LOG_ER("Can't init GLEW!");
				return false;
			}

			LOG(glGetString(GL_VERSION));

			return true;
		}

		void window_resize(GLFWwindow * window, int width, int height)
		{
			GLCall(glViewport(0, 0, width, height));
		}

		void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
		{
			Window *win = (Window*) glfwGetWindowUserPointer(window);
			win->keys_[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->mouseButtons_[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window *win = (Window*)glfwGetWindowUserPointer(window);
			win->mouseX_ = xpos;
			win->mouseY_ = ypos;
		}

	}
}