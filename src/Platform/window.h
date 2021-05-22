
#include <functional>
#include <string>

#include "Event/Event.h"

/*
	Struct that has to do with all the properties of the 
	current window. This is the height, width and title
	for instance for now
*/

struct WindowProperties
{
	using EventCallbackFn = std::function<void(Event& _event)>;
	
	EventCallbackFn event_callback;
	std::string name;
	uint32_t width;
	uint32_t height;

	WindowProperties(std::string _name = "Placeholder",
		uint32_t _width = 800,
		uint32_t _height = 600)
		: name(_name), width(_width), height(_height)
	{

	}
};

/*
	Platform independent class for
	the window of the application
*/

class Window
{
public:
	using EventCallbackFn = std::function<void(Event& _event)>;

public:
	virtual ~Window() {};
	virtual void update() = 0;

	virtual uint32_t get_width() const = 0;
	virtual uint32_t get_height() const = 0;

	virtual void set_event_callback(const EventCallbackFn& _callback) = 0;

	static Window* create_window(const WindowProperties& _properties = WindowProperties());
};

#ifdef MINESWEEPER_PLATFORM_LINUX
	static_assert(false, "Windows Only Support");
#endif
