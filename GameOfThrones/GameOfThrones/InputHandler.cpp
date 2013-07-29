#include "InputHandler.h"
#include <GL\glfw.h>
#include <iostream>

//#include <iostream>

InputHandler::InputHandler(void)
{
	mouseWheel = 0;
	oldMouseWheel = 0;
}

//Handles keyboard and mouse input.
void InputHandler::handleInput()
{
	pollKeyboard();
	pollMouse();
	pollGamepads();
}

void InputHandler::pollGamepads()
{
	glfwGetJoystickButtons(GLFW_JOYSTICK_1, p1Input, 10);
	glfwGetJoystickButtons(GLFW_JOYSTICK_2, p2Input, 10);

	glfwGetJoystickPos(GLFW_JOYSTICK_1, p1Axis, 5);
	glfwGetJoystickPos(GLFW_JOYSTICK_2, p2Axis, 5);
	//getting rid of noise in the data
	for(int i = 0; i < 5; i++)
	{
		if(abs(p1Axis[i]) < 0.15) p1Axis[i] = 0;
		if(abs(p2Axis[i]) < 0.15) p2Axis[i] = 0;
	}

}

void InputHandler::pollKeyboard()
{
	oldSpace = space;
	w = glfwGetKey('W');
	a = glfwGetKey('A');	
	s = glfwGetKey('S');	
	d = glfwGetKey('D');
	space = glfwGetKey(GLFW_KEY_SPACE);
	esc = glfwGetKey(GLFW_KEY_ESC);
}

void InputHandler::pollMouse()
{
	oldMousePos.x = mPosX;
	oldMousePos.y =	mPosY;
	glfwGetMousePos(&mPosX, &mPosY);
	oldMouseWheel = mouseWheel;
	mouseWheel = glfwGetMouseWheel();
	mLeftClick = glfwGetMouseButton(GLFW_MOUSE_BUTTON_LEFT);
	mRightClick = glfwGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT);
	mMiddleClick = glfwGetMouseButton(GLFW_MOUSE_BUTTON_MIDDLE);

	
}

InputHandler::~InputHandler(void)
{
}
