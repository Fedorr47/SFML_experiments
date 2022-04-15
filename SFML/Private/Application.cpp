#include "stdafx.h"

#include "Application.h"
#include "Window.h"

#include "Game\CustomLogic.h"

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application(std::string TitleName) :
	mTitleName{ std::move(TitleName) }
{
	mWindow = Window::GetInstance("SpaceWar");
	
	// Template to close window
	std::unique_ptr<Binding> bind = std::make_unique<Binding>("Window_Close");
	EventInfo eventInfo;
	eventInfo.mCode = 0;
	EventType type = static_cast<EventType>(static_cast<EventType>(0));
	bind->BindEvent(type, eventInfo);
	mWindow->GetEventManager()->AddBinding(std::move(bind));
	mWindow->GetEventManager()->AddCallback(mWindow->GetEventManager()->GetCurrentState(), "Window_Close", &Window::Close, mWindow);
}

sf::Time Application::GetElapsed()
{
	return mClock.getElapsedTime();
}

void Application::Run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (!mWindow->IsDone())
	{
		sf::Time dt = clock.restart();
		timeSinceLastUpdate += dt;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			Update();
			PostUpdate();
		}
		Render();
	}
}

void Application::Update()
{
	mWindow->Update();
	// TODO: place custom update here
}

void Application::Render()
{
	mWindow->BeginDraw();
	// TODO: place custom render here
	CustomLogic customlogic;
	customlogic.Render(mWindow->GetRenderWindow());
	//
	mWindow->EndDraw();
}

void Application::PostUpdate()
{
	RestartClock();
}

void Application::RestartClock()
{
	mElapsed = mClock.restart();
}

