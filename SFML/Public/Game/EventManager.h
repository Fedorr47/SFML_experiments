#pragma once

#include <functional>

class Action
{
	friend class ActionTarget;
	friend class hash;
	sf::Event mEvent;
	int mType;
public:
	enum Type
	{
		RealTime=1,
		Pressed=(1<<1),
		Released=(1<<2)
	};

	Action(const sf::Keyboard::Key& InKey, int InType = Type::RealTime | Type::Pressed);
	Action(const sf::Mouse::Button& InButton, int InType = Type::RealTime | Type::Pressed);

	Action(const Action& Other);
	Action& operator=(const Action& Other);

	bool Test() const;

	int GetType() const { return mType; }
	const sf::Event& GetEvent() const { return mEvent; }

	bool operator==(const sf::Event& Event) const;
	bool operator==(const Action& Other) const;

};

template<>
struct std::hash<Action>
{
	std::size_t operator()(Action const& action) const noexcept
	{
		std::size_t h1 = std::hash<int>{}(action.GetType());
		std::size_t h2 = std::hash<int>{}(action.GetEvent().key.code | action.GetEvent().mouseButton.button);
		return h1 ^ (h2 << 1);
	}
};

class ActionTarget
{
public:
	using FuncType = std::function<void(const sf::Event&)>;

	ActionTarget();

	bool ProcessEvents(const sf::Event& Event) const;
	void ProcessEvents() const;

	void Bind(const Action& InAction, const FuncType& Callback);
	void UnBind(const Action& InAction);

private:
	std::unordered_map<Action, FuncType> mEventsRealTime;
	std::unordered_map<Action, FuncType> mEventsPool;
};

