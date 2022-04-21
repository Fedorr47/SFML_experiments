#include "stdafx.h"

#include "Player.h"

#include <numbers>

Player::Player() :
	mShape{ 32,3 },
	mVelocity{ 0.0f, 0.0f },
	mIsMoving{ false },
	mRotation{ 0.0f }
{
	mShape.setFillColor(sf::Color::Blue);
	mShape.setOrigin(mShape.getLocalBounds().width/2, mShape.getLocalBounds().height / 2);

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

	mShape.setPosition(100, 100);
}

void Player::draw(sf::RenderTarget& Target, sf::RenderStates States) const
{
	Target.draw(mShape, States);
}

void Player::Update(sf::Time DeltaTime)
{
	float Seconds = DeltaTime.asSeconds();
	if (GetRotation() != 0)
	{
		float Angle = mShape.getRotation();
		Angle += mRotation * Seconds;
		mShape.setRotation(Angle);
	}
	if (IsMoving())
	{
		sf::Vector2f Velocity = GetVelocity();
		float Angle = (std::numbers::pi * mShape.getRotation()) / 180 - std::numbers::pi/2;
		Velocity = sf::Vector2f(std::cos(Angle), std::sin(Angle)) * Seconds;
		mShape.move(Velocity * 0.2f);
		SetVelocity(Velocity);
	}
}

void Player::ProcessEvents()
{
	mIsMoving = false;
	mRotation = 0.0f;
	ActionTarget::ProcessEvents();
}
