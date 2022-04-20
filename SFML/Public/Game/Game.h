#pragma once

#include "Game\Player.h"

class Game
{
	std::string mTitleName;

	static const sf::Time TimePerFrame;

	class Window* mWindow;

	sf::Clock mClock;
	sf::Time mElapsed;

	std::unique_ptr<Player> mPlayerPtr;

	void Update(sf::Time DeltaTime);
	void Render();

	void RestartClock();

public:
	explicit Game(std::string TitleName);
	
	~Game() {};

	sf::Time GetElapsed();

	void ProcessEvents() const;

	const Player& GetPlayer() const { return *mPlayerPtr.get(); }

	void Run();
};
