#include "InputMapping.h"

#include <iostream>


void InputMapping::update(GLFWwindow* window, InputState& state)
{
	state.actions.clear();
	for (const auto& [key, action] : keyBindings)
	{
		if (glfwGetKey(window, key) == GLFW_PRESS)
		{
			state.actions[action] = true;
		}


		//state.mouseDelta = glm::vec2(0.0f);
	}

	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	glm::vec2 currentMouse = glm::vec2(xpos, ypos);

	if (state.firstMoues)
	{
		state.mousePosition = currentMouse;
		state.mouseDelta = glm::vec2(0.0f);
		state.firstMoues = false;
		// std::cout<< "mouse pos initialized" << std::endl;
	}
	else
	{
		// calculate mouse delta
		state.mouseDelta = currentMouse - state.mousePosition;
		state.mousePosition = currentMouse;

		//std::cout << " mouseDelta: " << state.mouseDelta.y << std::endl;
	}
}