#ifndef LOCALIZATION_H
#define LOCALIZATION_H


enum LOCALIZABLE_STRINGS : unsigned short {LOC_TITLE = 0, LOC_TITLE_FIRST = 1, LOC_TITLE_LAST = 2, LOC_START_PROMPT = 3};


class Localization {
private:
	static const unsigned short LOCALIZED_STRINGS_COUNT = 4;
	const char* text[LOCALIZED_STRINGS_COUNT] = {"STRIFE SLOOPS", "STRIFE", "SLOOPS", "Press Any Key"};

	static const constexpr char* ERROR_TEXT = "error";
public:
	Localization();

	const char* getLocalizedString(const unsigned short index);
};

#endif