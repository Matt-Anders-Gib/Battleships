#include "Arduino.h"


enum BUTTON_STATE : unsigned short {BUTTON_UP = 0, BUTTON_DOWN = 1, BUTTON_ACTIVE = 2};


class Button {
private:
	BUTTON_STATE state = BUTTON_STATE::BUTTON_UP;
	unsigned short maxInputValue;
	unsigned short minInputValue;
	void (*downAction)();

public:
	Button() {}
	Button(const unsigned short minVal, const unsigned short maxVal, void (*downCallback)()) {
		maxInputValue = maxVal;
		minInputValue = minVal;
		downAction = downCallback;
	}
};


static const uint8_t INTERACTION_BUTTONS_PIN = A0;
static const constexpr unsigned char MAX_NOISE_THRESHOLD = 10;

short interactionButtonsValue = 0;

Button buttons[2];


void buttonPressed_A() {
	Serial.println(F("[A]"));
}

void buttonPressed_B() {
	Serial.println(F("[B]"));
}


void setup() {
	pinMode(INTERACTION_BUTTONS_PIN, INPUT);

	buttons[0] = Button(675, 685, &buttonPressed_A);
	buttons[1] = Button(300, 400, &buttonPressed_B);

	Serial.begin(9600);
	while (!Serial) {
		delay(250);
	}

	Serial.println(F("Running!"));
}


void updateButtonStates() {
	interactionButtonsValue = analogRead(INTERACTION_BUTTONS_PIN);
}


void loop() {
	updateButtonStates();

	if (interactionButtonsValue > MAX_NOISE_THRESHOLD) {
		/*if (interactionButtonsValue < A_BUTTON_MAX_THRESHOLD &&
			interactionButtonsValue > A_BUTTON_MIN_THRESHOLD) {
			buttonPressed_A();
		} else {
			if (interactionButtonsValue < B_BUTTON_THRESHOLD) {
				buttonPressed_B();
			}
		}*/
	}
}
