#include "stdafx.h"

#include "Player.h"

#include <numbers>

ActionMap<int> Player::MapPlayerInputs;

Player::Player() :
	ActionTarget(MapPlayerInputs),
	mShape{ 32,3 },
	mVelocity{ 0.0f, 0.0f },
	mIsMoving{ false },
	mRotation{ 0.0f },
	mDirection{ Direction::NONE }
{
	SetDefaultPlayerInputs();
	mShape.setFillColor(sf::Color::Blue);
	mShape.setOrigin(mShape.getLocalBounds().width / 2, mShape.getLocalBounds().height / 2);

	Bind(PlayerInputs::Up, [this](const sf::Event&)
	{
		mIsMoving = true;
		mDirection = Direction::Forward;
	}
	);

	Bind(PlayerInputs::Down, [this](const sf::Event&)
	{
		mIsMoving = true;
		mDirection = Direction::ForwardBack;
	}
	);

	Bind(PlayerInputs::Left, [this](const sf::Event&)
	{
		mRotation -= 0.5;
	}
	);

	Bind(PlayerInputs::Right, [this](const sf::Event&)
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
		float lDirection = mDirection == Direction::Forward ? 1.0f : -1.0f;
		sf::Vector2f Velocity = GetVelocity();
		float Angle = (std::numbers::pi * mShape.getRotation()) / 180 - std::numbers::pi/2;
		Velocity = sf::Vector2f(std::cos(Angle), std::sin(Angle)) * Seconds;
		mShape.move(Velocity * 0.2f * lDirection);
		SetVelocity(Velocity);
	}
}

void Player::ProcessEvents()
{
	mIsMoving = false;
	mRotation = 0.0f;
	mDirection = Direction::NONE;
	ActionTarget::ProcessEvents();
}

void Player::SetDefaultPlayerInputs()
{
	MapPlayerInputs.AddToMap(PlayerInputs::Up, Action(sf::Keyboard::Up));
	MapPlayerInputs.AddToMap(PlayerInputs::Left, Action(sf::Keyboard::Left));
	MapPlayerInputs.AddToMap(PlayerInputs::Right, Action(sf::Keyboard::Right));
	MapPlayerInputs.AddToMap(PlayerInputs::Down, Action(sf::Keyboard::Down));
}
