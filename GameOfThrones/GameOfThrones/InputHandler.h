#pragma once
#include <glm\glm.hpp>

class InputHandler
{
public:
	/*Buttons of the first connected Xbox controller.
	 * 0 = A
	 * 1 = B
	 * 2 = X
	 * 3 = Y
	 * 4 = LB
	 * 5 = RB
	 * 6 = back
	 * 7 = start
	 * 8 = left stick click
	 * 9 = right stick click
	*/
	unsigned char p1Input[10];
	unsigned char p2Input[10];
	/*Axis of the first connected Xbox controller.
	 * 0 is left x
	 * 1 is left y
	 * 2 is trigger buttons
	 * 3 is right x
	 * 4 is right y */
	float p1Axis[5];
	float p2Axis[5];
	bool w;
	bool a;
	bool s;
	bool d;
	int mPosX;
	int mPosY;
	int mouseWheel;
	bool mLeftClick;
	bool mRightClick;
	bool mMiddleClick;
	bool esc;

	bool space;
	bool oldSpace;

	glm::vec2 oldMousePos;
	int oldMouseWheel;

	InputHandler(void);

	void handleInput();
	
	~InputHandler(void);

private:
	void pollKeyboard();
	void pollMouse();
	void pollGamepads();
};
