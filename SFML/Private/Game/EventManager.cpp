#include "stdafx.h"

#include "EventManager.h"

#include <unordered_map>

Action::Action(const sf::Keyboard::Key& InKey, int InType) :
	mType{InType}
{
	mEvent.type = sf::Event::EventType::KeyPressed;
	mEvent.key.code = InKey;
}

Action::Action(const sf::Mouse::Button& InButton, int InType) :
	mType{ InType }
{
	mEvent.type = sf::Event::EventType::MouseButtonPressed;
	mEvent.mouseButton.button = InButton;
}

Action::Action(const Action& Other) :
	mType{ Other.mType }
{
	std::memcpy(&mEvent, &Other.mEvent, sizeof(sf::Event));
}

Action& Action::operator=(const Action& Other)
{
	if (this == &Other)
	{
		return *this;
	}

	std::memcpy(&mEvent, &Other.mEvent, sizeof(sf::Event));
	mType = Other.mType;
	return *this;
}

bool Action::Test() const
{
	bool Result = false;
	if (mEvent.type == sf::Event::KeyPressed && mType & Type::Pressed)
	{
		Result = sf::Keyboard::isKeyPressed(mEvent.key.code);
	}
	else if (mEvent.type == sf::Event::MouseButtonPressed && mType & Type::Pressed)
	{
		Result = sf::Mouse::isButtonPressed(mEvent.mouseButton.button);
	}
	return Result;
}

bool Action::operator==(const sf::Event& Event) const
{
	bool Result = false;
	switch (Event.type)
	{
		case sf::Event::KeyPressed:
		{
			if (mType & Type::Pressed && mEvent.type == sf::Event::KeyPressed)
			{
				Result = Event.key.code == mEvent.key.code;
			}
		}
		case sf::Event::KeyReleased:
		{
			if (mType & Type::Released && mEvent.type == sf::Event::KeyReleased)
			{
				Result = Event.key.code == mEvent.key.code;
			}
		}
		case sf::Event::MouseButtonPressed:
		{
			if (mType & Type::Pressed && mEvent.type == sf::Event::MouseButtonPressed)
			{
				Result = Event.mouseButton.button == mEvent.mouseButton.button;
			}
		}
		case sf::Event::MouseButtonReleased:
		{
			if (mType & Type::Released && mEvent.type == sf::Event::MouseButtonReleased)
			{
				Result = Event.mouseButton.button == mEvent.mouseButton.button;
			}
		}
		default:
			break;
	}
	return Result;
}

bool Action::operator==(const Action& Other) const
{
	return mType == Other.mType && Other == mEvent;
}

