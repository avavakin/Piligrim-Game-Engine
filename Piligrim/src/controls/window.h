#pragma once
#define GLEW_STATIC
#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../utils/logs.h"
#include "../utils/glcall.h"

#include "controllers/Controller.h"
#include "controllers/IControlsObserver.h"





class Window : public IControlsObserver
{
public:
	Window(const std::string& title, int width, int height);
	~Window();

	void clear() const;
	void update();
	bool closed() const;

	int getWidth() const;
	int getHeight() const;

	void connectController(Controller& controller);

	void onControllerEvent(Controller* controller, double deltaTime);

private:
	std::string title_;
	int width_, height_;
	GLFWwindow* window_;

	ControlsTable* controlsTable_;
private:
	bool init();

	friend static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	friend static void mouse_button_callback(GLFWwindow * window, int button, int action, int mods);
	friend static void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
	friend static void window_resize(GLFWwindow * window, int width, int height);
};