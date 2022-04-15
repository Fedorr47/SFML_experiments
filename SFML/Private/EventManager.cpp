#include "stdafx.h"

#include "EventManager.h"
#include <cstring>

EventManager::EventManager() : 
	mCurrentState(StateType(0)), 
	mHasFocus(true)
{
	LoadBindings();
}

EventManager::~EventManager()
{
}

void EventManager::LoadBindings()
{
}

void EventManager::AddBinding(std::unique_ptr<Binding> Binding)
{
	if (mBindings.find(Binding->mName) != mBindings.end())
		return;

	mBindings.emplace(Binding->mName, std::move(Binding));
}

bool EventManager::RemoveBinding(std::string Name)
{
	auto BindingItr = mBindings.find(Name);
	if (BindingItr == mBindings.end())
	{ 
		return false; 
	}
	mBindings.erase(BindingItr);
	return true;
}

void EventManager::HandleEvent(sf::Event& InEventType) 
{
	EventType sfmlEvent = (EventType)InEventType.type;

	for (auto& BindingItr : mBindings) 
	{
		Binding& bind = *BindingItr.second;
		for (auto& EventItr : bind.mEvents) 
		{
			if (EventItr.first != sfmlEvent) 
			{ 
				continue; 
			}
			else if (sfmlEvent == EventType::Closed)
			{
				++(bind.EventCount);
				break;
			}
			else if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp) 
			{
				if (EventItr.second.mCode == InEventType.key.code) 
				{
					if (bind.mDetails.mKeyCode != -1) {
						bind.mDetails.mKeyCode = EventItr.second.mCode;
					}
					++(bind.EventCount);
					break;
				}
			}
			else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp) 
			{
				if (EventItr.second.mCode == InEventType.mouseButton.button) 
				{
					bind.mDetails.mMouse.x = InEventType.mouseButton.x;
					bind.mDetails.mMouse.y = InEventType.mouseButton.y;
					if (bind.mDetails.mKeyCode != -1) {
						bind.mDetails.mKeyCode = EventItr.second.mCode;
					}
					++(bind.EventCount);
					break;
				}
			}
			else 
			{
				// No need for additional checking.
				if (sfmlEvent == EventType::MouseWheel) {
					bind.mDetails.mMouseWheelDelta = InEventType.mouseWheel.delta;
				}
				else if (sfmlEvent == EventType::WindowResized) {
					bind.mDetails.mSize.x = InEventType.size.width;
					bind.mDetails.mSize.y = InEventType.size.height;
				}
				else if (sfmlEvent == EventType::TextEntered) {
					bind.mDetails.mTextEntered = InEventType.text.unicode;
				}
				++(bind.EventCount);
			}
		}
	}
}

void EventManager::Update()
{
	if (!mHasFocus)
	{ 
		return;
	}
	for (auto & BindingItr : mBindings)
	{
		Binding& bind = *BindingItr.second;

		if(bind.mEvents.size() > 0 && bind.EventCount > 0)
		{
			auto stateCallbacks = mCallbacks.find(mCurrentState);
			auto otherCallbacks = mCallbacks.find(StateType(0));

			if(stateCallbacks != mCallbacks.end())
			{
				auto callItr = stateCallbacks->second.find(bind.mName);
				if(callItr != stateCallbacks->second.end()){
					callItr->second(&bind.mDetails);
				}
			}

			if(otherCallbacks != mCallbacks.end())
			{
				auto callItr = otherCallbacks->second.find(bind.mName);
				if(callItr != otherCallbacks->second.end()){
					callItr->second(&bind.mDetails);
				}
			}
		}
		bind.EventCount = 0;
		bind.mDetails.Clear();
	}
}
