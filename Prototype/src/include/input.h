#ifndef INPUT_H
#define INPUT_H


#include "Arduino.h"


//TIE-DOWN_RESISTANCE = 10000 Ohms

//NOTE: +-1 Margin Added

//A_BUTTON_RESISTANCE = 1000 Ohms
const static constexpr unsigned short A_BUTTON_MIN = 920;
const static constexpr unsigned short A_BUTTON_MAX = 950;
const static constexpr unsigned short A_BUTTON_RANGE = A_BUTTON_MAX - A_BUTTON_MIN;

//B_BUTTON_RESISTANCE = 1540 Ohms
const static constexpr unsigned short B_BUTTON_MIN = 875;
const static constexpr unsigned short B_BUTTON_MAX = 905;
const static constexpr unsigned short B_BUTTON_RANGE = B_BUTTON_MAX - B_BUTTON_MIN;

//C_BUTTON_RESISTANCE = 2000 Ohms
const static constexpr unsigned short C_BUTTON_MIN = 845;
const static constexpr unsigned short C_BUTTON_MAX = 870;
const static constexpr unsigned short C_BUTTON_RANGE = C_BUTTON_MAX - C_BUTTON_MIN;

const static constexpr unsigned short AB_BUTTON_MIN = 880;
const static constexpr unsigned short AB_BUTTON_MAX = 985;
const static constexpr unsigned short AB_BUTTON_RANGE = AB_BUTTON_MAX - AB_BUTTON_MIN;

const static constexpr unsigned short AC_BUTTON_MIN = 845;
const static constexpr unsigned short AC_BUTTON_MAX = 971;
const static constexpr unsigned short AC_BUTTON_RANGE = AC_BUTTON_MAX - AC_BUTTON_MIN;

const static constexpr unsigned short BC_BUTTON_MIN = 880;
const static constexpr unsigned short BC_BUTTON_MAX = 955;
const static constexpr unsigned short BC_BUTTON_RANGE = BC_BUTTON_MAX - BC_BUTTON_MIN;

const static constexpr unsigned short ABC_BUTTON_MIN = 880;
const static constexpr unsigned short ABC_BUTTON_MAX = 1000;
const static constexpr unsigned short ABC_BUTTON_RANGE = ABC_BUTTON_MAX - ABC_BUTTON_MIN;


static const unsigned short INPUT_PIN = A0;


enum class BUTTON {BTN_NONE, BTN_A, BTN_B, BTN_C, BTN_AB, BTN_AC, BTN_BC, BTN_ABC};

struct ButtonEvent {
	BUTTON button;
	char identifier;
	bool pressed;

	ButtonEvent() {
		button = BUTTON::BTN_NONE;
		identifier = '!';
		pressed = false;
	}

	ButtonEvent(BUTTON b, char i, bool p) {
		button = b;
		identifier = i;
		pressed = p;
	}

	bool operator==(const ButtonEvent& o) {
		return (button == o.button && pressed == o.pressed);
	}

	bool operator!=(const ButtonEvent& o) {
		return !(*this == o);
	}
};
const ButtonEvent BUTTON_EVENT_NONE = ButtonEvent(BUTTON::BTN_NONE, 'N', false);



class Input {
private:
	static const unsigned short GROUND_THRESHOLD_VALUE = 50;

	static const unsigned short INPUT_SEARCH_MS = 70; //Period to wait for additional inputs before reporting button press. Button Down is triggered at the end of the input search period

	unsigned short inputVoltageLevel = 0;
	unsigned short highestInputVoltageLevel = 0;

	unsigned long long nowMS = 0;
	
	bool buttonPressedLastFrame = false;
	unsigned long long inputStartTime = 0;
	bool inputProcessed = true;

	ButtonEvent event = BUTTON_EVENT_NONE;

	ButtonEvent down(const unsigned short voltageLevel);
	ButtonEvent up();
public:
	ButtonEvent poll();
};

#endif