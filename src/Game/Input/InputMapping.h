#pragma once

#include <GLFW/glfw3.h>
#include <map>

#include "Game/Input/InputState.h"

class InputMapping
{
public:
	InputMapping() {
		keyBindings[GLFW_KEY_W] = InputAction::MoveForward;
		keyBindings[GLFW_KEY_S] = InputAction::MoveBackward;
		keyBindings[GLFW_KEY_A] = InputAction::MoveLeft;
		keyBindings[GLFW_KEY_D] = InputAction::MoveRight;
		keyBindings[GLFW_KEY_ESCAPE] = InputAction::Quit;
	}

	void update(GLFWwindow* window, InputState& state);

private:
	std::unordered_map<int, InputAction> keyBindings;
};