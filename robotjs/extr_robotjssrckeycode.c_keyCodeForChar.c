#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  MMKeyCode ;

/* Variables and functions */

MMKeyCode keyCodeForChar(const char c)
{
#if defined(IS_MACOSX)
	/* OS X does not appear to have a built-in function for this, so instead we
	 * have to write our own. */
	static CFMutableDictionaryRef charToCodeDict = NULL;
	CGKeyCode code;
	UniChar character = c;
	CFStringRef charStr = NULL;

	/* Generate table of keycodes and characters. */
	if (charToCodeDict == NULL) {
		size_t i;
		charToCodeDict = CFDictionaryCreateMutable(kCFAllocatorDefault,
		                                           128,
		                                           &kCFCopyStringDictionaryKeyCallBacks,
		                                           NULL);
		if (charToCodeDict == NULL) return UINT16_MAX;

		/* Loop through every keycode (0 - 127) to find its current mapping. */
		for (i = 0; i < 128; ++i) {
			CFStringRef string = createStringForKey((CGKeyCode)i);
			if (string != NULL) {
				CFDictionaryAddValue(charToCodeDict, string, (const void *)i);
				CFRelease(string);
			}
		}
	}

	charStr = CFStringCreateWithCharacters(kCFAllocatorDefault, &character, 1);

	/* Our values may be NULL (0), so we need to use this function. */
	if (!CFDictionaryGetValueIfPresent(charToCodeDict, charStr,
	                                   (const void **)&code)) {
		code = UINT16_MAX; /* Error */
	}

	CFRelease(charStr);
	return (MMKeyCode)code;
#elif defined(IS_WINDOWS)
	return VkKeyScan(c);
#elif defined(USE_X11)
	MMKeyCode code;

	char buf[2];
	buf[0] = c;
	buf[1] = '\0';

	code = XStringToKeysym(buf);
	if (code == NoSymbol) {
		/* Some special keys are apparently not handled properly by
		 * XStringToKeysym() on some systems, so search for them instead in our
		 * mapping table. */
		size_t i;
		const size_t specialCharacterCount =
			sizeof(XSpecialCharacterTable) / sizeof(XSpecialCharacterTable[0]);
		for (i = 0; i < specialCharacterCount; ++i) {
			if (c == XSpecialCharacterTable[i].name) {
				code = XSpecialCharacterTable[i].code;
				break;
			}
		}
	}

	return code;
#endif
}