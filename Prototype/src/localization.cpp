#include "include/localization.h"


Localization::Localization() {

}


const char* Localization::getLocalizedString(const unsigned short index) {
	if(index < LOCALIZED_STRINGS_COUNT) {
		return text[index];
	} else {
		return ERROR_TEXT;
	}
}