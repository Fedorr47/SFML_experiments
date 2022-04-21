#include "EventManager.h"
template<class Key>
void ActionMap<Key>::AddToMap(const Key& InKey, const Action& InAction)
{
	mActionMap.emplace(InKey, InAction);
}

template<class Key>
const Action& ActionMap<Key>::Get(const Key& InKey) const
{
	mActionMap.find(InKey);
	return mActionMap.at(InKey);
}

template<class Key>
inline const bool ActionMap<Key>::Contains(const Key& InKey) const
{
	return mActionMap.contains(InKey);
}

template<class Key>
bool ActionTarget<Key>::ProcessEvents(const sf::Event& Event) const
{
	bool Result = false;
	for (const std::pair<Action, FuncType>& ActionPair : mEventsPool)
	{
		if (ActionPair.first == Event)
		{
			ActionPair.second(Event);
			Result = true;
			break;
		}
	}
	return Result;
}

template<class Key>
void ActionTarget<Key>::ProcessEvents() const
{
	for (const std::pair<Key, FuncType>& ActionPair : mEventsRealTime)
	{
		if (mActionMap.Contains(ActionPair.first))
		{
			const Action& lAction = mActionMap.Get(ActionPair.first);
			if (lAction.Test())
			{
				ActionPair.second(lAction.GetEvent());
			}
		}
	}
}

template<class Key>
void ActionTarget<Key>::Bind(const Key& InKey, const FuncType& Callback)
{
	if (mActionMap.Contains(InKey))
	{
		const Action& lAction = mActionMap.Get(InKey);

		if (lAction.GetType() & Action::Type::RealTime)
		{
			mEventsRealTime.emplace(InKey, Callback);
		}
		else
		{
			mEventsPool.emplace(InKey, Callback);
		}
	}
}

template<class Key>
void ActionTarget<Key>::UnBind(const Key& InKey)
{
	if (mActionMap.Contains(InKey))
	{
		const Action& lAction = mActionMap.Get(InKey);

		if (lAction.GetType() & Action::Type::RealTime)
		{
			mEventsRealTime.erase(InKey);
		}
		else
		{
			mEventsPool.erase(InKey);
		}
	}
}