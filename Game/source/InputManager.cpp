#include <InputManager.h>
#include <iostream>

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

void InputManager::update()
{
	//Update happens after everything else in the game.
	for (auto it = keyMap.begin(); it != keyMap.end();)
	{
		if (it->second == KeyStatus::Down)
		{
			it->second = KeyStatus::Held;
			++it;
		}
		else if (it->second == KeyStatus::Up)
		{
			keyMap.erase(it++);
		}
		else
		{
			++it;
		}
	}

	//send the current mouse position to the previous mouse position in preparation for the next frame
	previousMousePos.x = mousePos.x;
	previousMousePos.y = mousePos.y;

	//reset the characters string for the next frame of inputs
	characters = "";
}

void InputManager::sendInput(int inputCode, bool held)
{
	if (!held) //held inputs are discarded since they are not needed for our logic
	{
		//find() returns an iterator, and we can tell if it returns a hit by verifying that the iterator is not at the end of the list
		std::unordered_map<int, KeyStatus>::iterator it = keyMap.find(inputCode);
		if (it != keyMap.end())
			it->second = KeyStatus::Down; //if the key already exists in the list, update the value to being down (in case it's in held status)
		else
			keyMap.insert({ inputCode, KeyStatus::Down }); //otherwise, insert a new entry
	}
}

void InputManager::removeInput(int inputCode)
{
	//keyMap.erase(inputCode);
	std::unordered_map<int, KeyStatus>::iterator it = keyMap.find(inputCode);
	if (it != keyMap.end())
		it->second = KeyStatus::Up;
}

void InputManager::sendMousePos(float x, float y)
{
	mousePos.x = x;
	mousePos.y = y;

	if (mousePos.x > 65500) mousePos.x = 0; //weird thing that happens if you go right outside the bounds on the left, the number shoot way up
	if (mousePos.x > 65500) mousePos.y = 0; //it never happened for y, but better to be safe
}

bool InputManager::keyDown(KeyCode keyCode)
{
	std::unordered_map<int, KeyStatus>::iterator it = keyMap.find((int)keyCode);
	if (it != keyMap.end() && it->second == KeyStatus::Down) //if the key exists and it was pressed this frame
		return true;
	else
		return false;
}

bool InputManager::keyDown(char keyCode)
{
	std::unordered_map<int, KeyStatus>::iterator it = keyMap.find((int)keyCode);
	if (it != keyMap.end() && it->second == KeyStatus::Down) //if the key exists and it was pressed this frame
		return true;
	else
		return false;
}

bool InputManager::keyHeld(KeyCode keyCode)
{
	std::unordered_map<int, KeyStatus>::iterator it = keyMap.find((int)keyCode);
	if (it != keyMap.end() && it->second == KeyStatus::Held) //if the key exists and it was pressed this frame
		return true;
	else
		return false;
}

void InputManager::sendMouseVelocity(float x, float y)
{
	mouseVelocity.x = x;
	mouseVelocity.y = y;
}

void InputManager::sendCharacter(char character)
{
	//validate that this is a character that can be typed on the screen
	if (validateChar(character))
	{
		characters += character;
	}
}

bool InputManager::keyUp(KeyCode keyCode)
{
	std::unordered_map<int, KeyStatus>::iterator it = keyMap.find((int)keyCode);
	if (it != keyMap.end() && it->second == KeyStatus::Up) //if the key exists and it was pressed this frame
		return true;
	else
		return false;
}

std::string InputManager::getCharacters()
{
	return characters;
}

OVec2 InputManager::getMousePos()
{
	return mousePos;
}

OVec2 InputManager::getPreviousMousePos()
{
	return previousMousePos;
}

OVec2 InputManager::getMouseMovement()
{
	OVec2 result = mousePos - previousMousePos;
	return result;
}

OVec2 InputManager::getMouseVelocity()
{
	return mouseVelocity;
}

bool InputManager::validateChar(char character)
{
	if (character >= 32 && character <= 126) //https://www.learncpp.com/cpp-tutorial/chars/, this includes every character that can be displayed (spaces as well)
		return true;

	return false;
}
