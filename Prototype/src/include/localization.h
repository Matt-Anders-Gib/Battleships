#ifndef LOCALIZATION_H
#define LOCALIZATION_H


enum LOCALIZABLE_STRINGS : unsigned short {LOC_TITLE = 0, LOC_TITLE_FIRST = 1, LOC_TITLE_LAST = 2, LOC_START_PROMPT = 3, LOC_PLAY = 4, LOC_OPTIONS = 5, LOC_QUIT = 6};


class Localization {
private:
	static const unsigned short LOCALIZED_STRINGS_COUNT = 7;
	const char* text[LOCALIZED_STRINGS_COUNT] = {"STRIFE SLOOPS", "STRIFE", "SLOOPS", "Press Any Key", "Battle", "Options", "Quit"};

	static const constexpr char* ERROR_TEXT = "error";
public:
	Localization();

	const char* getLocalizedString(const unsigned short index);
};

#endif