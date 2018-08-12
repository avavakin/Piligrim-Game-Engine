#include "window.h"

namespace piligrim {
	namespace controls {

		Window::Window(const std::string& title, int width, int height)
		{
			title_ = title;
			height_ = height;
			width_ = width;

			if (!init()) {
				glfwTerminate();
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
			return glfwWindowShouldClose(window_) == GLFW_TRUE;
		}



		int Window::getWidth() const
		{
			return width_;
		}



		int Window::getHeight() const
		{
			return height_;
		}

		void Window::connectController(Controller& controller)
		{
			controlsTable_ = &controller.controlsTable_;
		}

		void Window::onControllerEvent(Controller* controller, double deltaTime)
		{
			bool needWindowClose = controller->isKeyActive(KeyRole::Escape);

			if (needWindowClose) {
				glfwSetWindowShouldClose(window_, GLFW_TRUE);
			}
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
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->controlsTable_->keyStates[key] = action;
		}



		void mouse_button_callback(GLFWwindow * window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->controlsTable_->keyStates[button] = action;
		}



		void cursor_position_callback(GLFWwindow * window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->x_ = xpos;
			win->y_ = ypos;
		}



	}
}