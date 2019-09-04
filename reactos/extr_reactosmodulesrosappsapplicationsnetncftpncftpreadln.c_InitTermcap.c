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

/* Variables and functions */
 scalar_t__ ISTRCMP (char const*,char*) ; 
 char* gCurXtermTitleStr ; 
 char* gTerm ; 
 int gXterm ; 
 int gXtermTitle ; 
 char* getenv (char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 char* tcap_boldface ; 
 char* tcap_normal ; 
 char* tcap_reverse ; 
 char* tcap_underline ; 

void
InitTermcap(void)
{
#if (defined(WIN32) || defined(_WINDOWS)) && defined(_CONSOLE)
	gXterm = gXtermTitle = 0;
	gCurXtermTitleStr[0] = '\0';

	tcap_normal = "";
	tcap_boldface = "";
	tcap_underline = "";
	tcap_reverse = "";

	gTerm = "MS-DOS Prompt";
	ZeroMemory(gSavedConsoleTitle, (DWORD) sizeof(gSavedConsoleTitle));
	GetConsoleTitle(gSavedConsoleTitle, (DWORD) sizeof(gSavedConsoleTitle) - 1);
	SetConsoleTitle("NcFTP");
	gXterm = gXtermTitle = 1;
#else
	const char *term;

	gXterm = gXtermTitle = 0;
	gCurXtermTitleStr[0] = '\0';

	if ((gTerm = getenv("TERM")) == NULL) {
		tcap_normal = "";
		tcap_boldface = "";
		tcap_underline = "";
		tcap_reverse = "";
		return;
	}

	term = gTerm;
	if (	(strstr(term, "xterm") != NULL) ||
		(strstr(term, "rxvt") != NULL) ||
		(strstr(term, "dtterm") != NULL) ||
		(ISTRCMP(term, "scoterm") == 0)
	) {
		gXterm = gXtermTitle = 1;
	}

	if (	(gXterm != 0) ||
		(strcmp(term, "vt100") == 0) ||
		(strcmp(term, "linux") == 0) ||
		(strcmp(term, "vt220") == 0) ||
		(strcmp(term, "vt102") == 0)
	) {
		tcap_normal = "\033[0m";       /* Default ANSI escapes */
		tcap_boldface = "\033[1m";
		tcap_underline = "\033[4m";
		tcap_reverse = "\033[7m";
	} else {
		tcap_normal = "";
		tcap_boldface = "";
		tcap_underline = "";
		tcap_reverse = "";
	}
#endif
}