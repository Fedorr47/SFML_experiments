#include "stdafx.h"

#include "Player.h"

#include <numbers>

Player::Player() :
	mShape{ sf::Vector2f(32,32) },
	mVelocity{ 0.0f, 0.0f },
	mIsMoving{ false },
	mRotation{ 0.0f }
{
	mShape.setFillColor(sf::Color::Blue);
	mShape.setOrigin(16, 16);

	Bind(Action(sf::Keyboard::Up), [this](const sf::Event&)
	{
		mIsMoving = true;
	}
	);

	Bind(Action(sf::Keyboard::Left), [this](const sf::Event&)
	{
		mRotation -= 0.5;
	}
	);

	Bind(Action(sf::Keyboard::Right), [this](const sf::Event&)
	{
		mRotation += 0.5;
	}
	);
}

void Player::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	Target.draw(mShape, States);
}

void Player::Update(sf::Time DeltaTime)
{
	float Seconds = DeltaTime.asSeconds();
	sf::Vector2f Velocity{0.0f,0.0f};
	if (GetRotation() != 0)
	{
		float Angle = mShape.getRotation();
		Angle += mRotation * Seconds;
		mShape.setRotation(Angle);
	}
	if (IsMoving())
	{
		float Angle = (std::numbers::pi * mShape.getRotation()) / 180;
		Velocity += sf::Vector2f(std::cos(Angle), std::sin(Angle));
	}
	mShape.move(Seconds * Velocity);
}

void Player::ProcessEvents()
{
	mIsMoving = false;
	mRotation = 0.0f;
	ActionTarget::ProcessEvents();
}
