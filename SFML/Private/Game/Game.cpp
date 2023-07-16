#include "stdafx.h"

#include "Game.h"
#include "Window.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game(std::string TitleName) :
	mTitleName{ std::move(TitleName) }
{
	mWindow = Window::GetInstance();
	mPlayerPtr = std::make_unique<Player>();
}

sf::Time Game::GetElapsed()
{
	return mClock.getElapsedTime();
}

void Game::ProcessEvents() const
{
	sf::Event Event;
	while (mWindow->GetRenderWindow().pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed ||
			(Event.type == sf::Event::KeyPressed &&
				Event.key.code == sf::Keyboard::Escape))
		{
			mWindow->Close();
		}
	}
	mPlayerPtr->ProcessEvents();
}

void Game::Run()
{
	bool Repaint = false;
	mClock.restart();
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (!mWindow->IsDone())
	{
		ProcessEvents();
		Repaint = false;

		sf::Time dt = mClock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			Repaint = true;
			Update(TimePerFrame);
		}
		Update(timeSinceLastUpdate);
		if (Repaint)
		{
			Render();
		}
	}
}

void Game::Update(sf::Time DeltaTime)
{
	// TODO: place custom update here
	mPlayerPtr->Update(DeltaTime);
}

void Game::Render()
{
	mWindow->BeginDraw();
	// TODO: place custom render here
	mWindow->Draw(GetPlayer());
	//
	mWindow->EndDraw();
}

void Game::RestartClock()
{
	mElapsed = mClock.restart();
}

