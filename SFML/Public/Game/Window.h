#pragma once

#include "EventManager.h"

class Window
{	
	sf::Vector2u mSize;
	std::string mTitle;
	bool mIsDone {false};
	bool mIsFullScreen {false};
	bool mIsFocused {false};
	sf::RenderWindow mWindow;
	std::shared_ptr<class EventManager> mEvenetManager;

public:

	static Window* GetInstance(const std::string Title = "Window", const sf::Vector2u Size = sf::Vector2u(640,480), sf::Uint32 Style = 0);
	~Window();
	
	void Create();

	void BeginDraw();
	void EndDraw();

	template <class ...Args>
	void Draw(Args&&... args)
	{
		mWindow.draw(std::forward<Args>(args)...);
	}
	
	bool IsDone() const { return mIsDone; };
	void Close();
	sf::Vector2u GetSize() { return mSize; }
	sf::RenderWindow& GetRenderWindow() { return mWindow; }
	std::shared_ptr<class EventManager> GetEventManager();

protected:

	Window(const std::string Title, const sf::Vector2u Size, sf::Uint32 Style);

	static Window* mWindowInstance;
};