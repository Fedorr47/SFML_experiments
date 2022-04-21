#pragma once

#include "EventManager.h"

class Player : public sf::Drawable, public ActionTarget<int>
{
	sf::CircleShape mShape;
	sf::Vector2f mVelocity{0.0f, 0.0f};

	enum Direction
	{
		Forward,
		ForwardBack,
		NONE
	};

	float mIsMoving{false};
	float mRotation{0.0f};
	Direction mDirection{ Direction::NONE };

	static ActionMap<int> MapPlayerInputs;
	
	Player(const Player& Other) = delete;
	Player& operator()(const Player& Other) = delete;

	virtual void draw(
		sf::RenderTarget& Target,
		sf::RenderStates States
	) const override;

public:

	Player();

	template <class ...Args>
	void SetPoistion(Args&&... args)
	{
		mShape.setPosition(std::forward<Args>(args)...);
	}

	void Update(sf::Time DeltaTime);

	const bool IsMoving() const { return mIsMoving; }

	void ProcessEvents();

	enum PlayerInputs
	{
		Up,
		Down,
		Left,
		Right
	};
	static void SetDefaultPlayerInputs();

	void SetVelocity(sf::Vector2f InVelocity) { mVelocity = InVelocity; }
	const sf::Vector2f GetVelocity() const { return mVelocity; }

	void SetRotation(float InRotation) { mRotation = InRotation; }
	const float GetRotation() const { return mRotation; }
};