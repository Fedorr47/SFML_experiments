#pragma once

#include "EventManager.h"

class Player : public sf::Drawable, public ActionTarget
{
	sf::RectangleShape mShape;
	sf::Vector2f mVelocity{0.0f, 0.0f};

	bool mIsMoving{false};
	float mRotation{0.0f};
	
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

	void SetVelocity(sf::Vector2f InVelocity) { mVelocity = InVelocity; }
	const sf::Vector2f GetVelocity() const { return mVelocity; }

	void SetRotation(float InRotation) { mRotation = InRotation; }
	const float GetRotation() const { return mRotation; }
};