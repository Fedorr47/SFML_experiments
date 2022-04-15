#pragma once
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <memory>

enum class EventType : uint32_t
{
	KeyDown = sf::Event::KeyPressed,
	KeyUp = sf::Event::KeyReleased,
	MButtonDown = sf::Event::MouseButtonPressed,
	MButtonUp = sf::Event::MouseButtonReleased,
	MouseWheel = sf::Event::MouseWheelMoved,
	WindowResized = sf::Event::Resized,
	GainedFocus = sf::Event::GainedFocus,
	LostFocus = sf::Event::LostFocus,
	MouseEntered = sf::Event::MouseEntered,
	MouseLeft = sf::Event::MouseLeft,
	Closed = sf::Event::Closed,
	TextEntered = sf::Event::TextEntered,
	Keyboard = sf::Event::Count + 1, 
	Mouse, 
	Joystick,
	GUI_Click,
	GUI_Release, 
	GUI_Hover, 
	GUI_Leave
};

struct EventInfo
{
	EventInfo() :
		mCode{0}
	{ }
	EventInfo(int InEventType) :
		mCode{ InEventType }
	{ }
	union {
		int mCode;
	};
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct EventDetails{
	EventDetails(const std::string& BindName)
		: mName(BindName)
	{
		Clear();
	}
	std::string mName;

	sf::Vector2i mSize;
	sf::Uint32 mTextEntered;
	sf::Vector2i mMouse;
	int mMouseWheelDelta;
	int mKeyCode; 

	void Clear(){
		mSize = sf::Vector2i(0, 0);
		mTextEntered = 0;
		mMouse = sf::Vector2i(0, 0);
		mMouseWheelDelta = 0;
		mKeyCode = -1;
	}
};

struct Binding {
	Binding(const std::string& Name) : 
		mName(Name),
		mDetails(Name), 
		EventCount(0) 
	{}
	~Binding() 
	{}
	void BindEvent(EventType InEventType, EventInfo Info) 
	{
		mEvents.emplace_back(InEventType, Info);
	}

	Events mEvents;
	std::string mName;
	int EventCount;

	EventDetails mDetails;
};

enum class StateType : uint8_t;

using Bindings = std::unordered_map<std::string, std::unique_ptr<Binding>>;
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
using Callbacks = std::unordered_map<StateType, CallbackContainer>;

class EventManager : std::enable_shared_from_this<EventManager>
{
public:
	std::shared_ptr<EventManager> GetPtr()
	{
		return shared_from_this();
	}

	[[nodiscard]] static std::shared_ptr<EventManager> Create() {
		return std::shared_ptr<EventManager>(new EventManager());
	}

	~EventManager();

	void AddBinding(std::unique_ptr<Binding> Binding);
	bool RemoveBinding(std::string Name);

	void SetCurrentState(const StateType InStateType) { mCurrentState = InStateType; }
	const StateType GetCurrentState() const { return mCurrentState; }

	void SetFocus(const bool& FocusState) { mHasFocus = FocusState; }

	template<class T>
	void AddCallback(
		StateType State, 
		const std::string& Name,
		void(T::* func)(EventDetails*),
		T* Instance)
	{
		auto itr = mCallbacks.emplace(State, CallbackContainer()).first;
		itr->second.emplace(Name, std::bind(func, Instance, std::placeholders::_1));
	}

	bool RemoveCallback(StateType State, const std::string& Name) {
		auto ItrStateCallbacks = mCallbacks.find(State);
		if (ItrStateCallbacks == mCallbacks.end())
		{ 
			return false; 
		}
		auto ItrConcreteCallback = ItrStateCallbacks->second.find(Name);
		if (ItrConcreteCallback == ItrStateCallbacks->second.end())
		{ 
			return false; 
		}
		ItrStateCallbacks->second.erase(Name);
		return true;
	}

	void HandleEvent(sf::Event& InEventType);
	void Update();

	sf::Vector2i GetMousePos(sf::RenderWindow* InWindow = nullptr) 
	{
		return (InWindow ? sf::Mouse::getPosition(*InWindow) : sf::Mouse::getPosition());
	}

private:
	EventManager();
	void LoadBindings();

	StateType mCurrentState;
	Bindings mBindings;
	Callbacks mCallbacks;
	bool mHasFocus;
};