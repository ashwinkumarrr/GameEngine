#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::vec2 MouseEventListener::mouse = glm::vec2();
glm::vec2 MouseEventListener::prevMouse = glm::vec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener()
{
	engineInstance = nullptr;
}
void MouseEventListener::RegisterEngineObject(CoreEngine* engine_)
{
	engineInstance = engine_;
}
void MouseEventListener::Update(SDL_Event e_)
{
	if (e_.type == SDL_MOUSEBUTTONDOWN)
	{
		UpdateMousePosition();
		NotifyOfMousePressed(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEBUTTONUP)
	{
		UpdateMousePosition();
		NotifyOfMouseReleased(e_.button.button);
	}
	else if (e_.type == SDL_MOUSEMOTION)
	{
		UpdateMousePosition();
		NotifyOfMouseMoved();
	}
	else if (e_.type == SDL_MOUSEWHEEL)
	{
		NotifyOfMouseScroll(e_.wheel.y);
	}
}

void MouseEventListener::NotifyOfMousePressed(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMousePressed(mouse);
	}
}
void MouseEventListener::NotifyOfMouseReleased(int buttonType_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseReleased(mouse, buttonType_);
	}
}
void MouseEventListener::NotifyOfMouseMoved()
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseMoved(mouse);
	}
}
void MouseEventListener::NotifyOfMouseScroll(int y_)
{
	if (engineInstance)
	{
		engineInstance->NotifyOfMouseScroll(y_);
	}
}

glm::vec2 MouseEventListener::GetPreviousMousePosition()
{
	return prevMouse;
}
glm::vec2 MouseEventListener::GetCurrentMousePosition()
{
	return mouse;
}
glm::vec2 MouseEventListener::GetMouseOffset()
{
	return glm::vec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePosition()
{
	int tempX, tempY;
	SDL_GetMouseState(&tempX, &tempY);
	tempY = engineInstance->GetWindowsize().y - tempY;
	if (firstUpdate)
	{
		prevMouse.x = mouse.x = tempX;
		prevMouse.y = mouse.y = tempY;
		firstUpdate = false; 
	}
	else
	{
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tempX;
		mouse.y = tempY;
	}
}