#ifndef EVENT_H
#define EVENT_H


class Event {
private:
public:
};

class Button;

class ButtonEvent : public Event {
private:
	Button& button;
	bool pressed;

	ButtonEvent(Button& b, bool p) : button{b}, pressed{p} {}
public:
};


#endif