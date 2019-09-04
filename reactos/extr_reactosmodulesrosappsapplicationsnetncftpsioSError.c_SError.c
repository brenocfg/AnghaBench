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
 int errno ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
SError(int e)
{
#if defined(WIN32) || defined(_WINDOWS)
	const char *cp;
	static char estr[32];

	if (e == 0)
		e = WSAGetLastError();

	if ((e >= WSABASEERR) && (e < (WSABASEERR + (sizeof(wsaerrlist) / sizeof(const char *))))) {
		return wsaerrlist[e - WSABASEERR];
	}

	cp = strerror(e);
	if ((cp == NULL) || (cp[0] == '\0') || (strcmp(cp, "Unknown error") == 0)) {
		wsprintf(estr, "Error #%d", e);
		cp = estr;
	}
	return cp;
#elif defined(HAVE_STRERROR)
	if (e == 0)
		e = errno;
	return strerror(e);
#else
	static char estr[32];
	if (e == 0)
		e = errno;
	sprintf(estr, "Error #%d", e);
	return (estr);
#endif
}