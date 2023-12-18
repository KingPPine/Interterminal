#pragma once
#include <Windows.h>
#include <unordered_map>
#include <OGL3D/Math/OVec2.h>
#include <string>

enum class KeyCode //enum of keycodes we'll process in the game so that it's more readable
{

	//VK_0 - VK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
	//0x3A - 0x40 : unassigned
	//VK_A - VK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
	MouseLeft = 1,
	MouseRight = 2,
	UpArrow = VK_UP,
	DownArrow = VK_DOWN,
	LeftArrow = VK_LEFT,
	RightArrow = VK_RIGHT,
	Space = VK_SPACE,
	Ctrl = VK_CONTROL,
	Enter = VK_RETURN,
	Backspace = VK_BACK,
	W = 'W',
	S = 'S',
	A = 'A',
	D = 'D',
};

enum class KeyStatus
{
	Down = 0,
	Held,
	Up
};

class InputManager
{
public:
	InputManager();
	~InputManager();

	void update();

	void sendInput(int inputCode, bool held);
	void removeInput(int inputCode);
	void sendMousePos(float x, float y);
	void sendMouseVelocity(float x, float y);
	void sendCharacter(char character);

	bool keyDown(KeyCode keyCode);
	bool keyDown(char keyCode);
	bool keyHeld(KeyCode keyCode);
	bool keyUp(KeyCode keyCode);
	std::string getCharacters();
	OVec2 getMousePos();
	OVec2 getPreviousMousePos();
	OVec2 getMouseMovement();
	OVec2 getMouseVelocity();

private:
	bool validateChar(char character);


private:
	std::unordered_map<int, KeyStatus> keyMap;
	std::string characters;
	OVec2 mousePos = OVec2();
	OVec2 previousMousePos = OVec2();
	OVec2 mouseVelocity = OVec2(); //sent by CWin32Window.cpp when the game isn't paused, since the cursor is fixed to the middle of the screen.
};

