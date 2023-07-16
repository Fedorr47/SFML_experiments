#include "stdafx.h"

#include "Window.h"

#include <string>
#include <memory>

#include "EventManager.h"

Window* Window::mWindowInstance = nullptr;

Window* Window::GetInstance(
	const std::string Title /*= "Window"*/, 
	const sf::Vector2u Size /*= sf::Vector2u(640,480)*/, 
	sf::Uint32 Style /* = sf::Style::Default*/)
{
	if (mWindowInstance == nullptr)
	{
		mWindowInstance = new Window(Title, Size, Style);
	}
	return mWindowInstance;
}

void Window::Close()
{
	mWindow.close();
	mIsDone = true;
}

std::shared_ptr<class EventManager> Window::GetEventManager()
{
	return mEvenetManager;
}

Window::Window(const std::string Title, const sf::Vector2u Size, sf::Uint32 Style) :
	mTitle(Title),
	mSize(Size),
	mIsFullScreen(Style == sf::Style::Default),
	mIsDone(false),
	mIsFocused(true)
{
	Create();
}

Window::~Window()
{
	delete mWindowInstance;
}

void Window::Create()
{
	sf::Uint32 Style = sf::Style::Default;
	if (mIsFullScreen)
	{
		Style = sf::Style::Fullscreen;
	}
	mWindow.create(sf::VideoMode(mSize.x, mSize.y, 32), "Window", Style);
}

void Window::BeginDraw()
{
	mWindow.clear(sf::Color::Black);
}

void Window::EndDraw()
{
	mWindow.display();
}


