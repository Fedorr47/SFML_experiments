#pragma once

class Application
{
	std::string mTitleName;

	static const sf::Time TimePerFrame;

	class Window* mWindow;

	sf::Clock mClock;
	sf::Time mElapsed;

	void Update();
	void Render();
	void PostUpdate();

	void RestartClock();

public:
	explicit Application(std::string TitleName);
	
	~Application() {};

	sf::Time GetElapsed();

	void Run();
};
