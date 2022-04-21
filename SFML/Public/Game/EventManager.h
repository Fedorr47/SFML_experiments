#pragma once

#include <functional>

class Action
{
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

template <class Key = int>
class ActionMap
{
	ActionMap(const ActionMap<Key>& Other) = delete;
	ActionMap<Key>& operator=(const ActionMap<Key>& Other) = delete;

	std::unordered_map<Key, Action> mActionMap;

public:
	ActionMap() = default;

	void AddToMap(const Key& InKey, const Action& InAction);
	const Action& Get(const Key& InKey) const;
	const bool Contains(const Key& InKey) const;
};

template <class Key>
class ActionTarget
{
	ActionTarget(const ActionTarget<Key>& Other) = delete;
	ActionTarget<Key>& operator=(const ActionTarget<Key>& Other) = delete;

public:
	using FuncType = std::function<void(const sf::Event&)>;
	
	ActionTarget(const ActionMap<Key>& InActionMap) :
		mActionMap{ InActionMap }
	{}

	bool ProcessEvents(const sf::Event& Event) const;
	void ProcessEvents() const;

	void Bind(const Key& InKey, const FuncType& Callback);
	void UnBind(const Key& InKey);

private:
	std::unordered_map<Key, FuncType> mEventsRealTime;
	std::unordered_map<Key, FuncType> mEventsPool;

	const ActionMap<Key>& mActionMap;
};

#include "EventManager.inl"
