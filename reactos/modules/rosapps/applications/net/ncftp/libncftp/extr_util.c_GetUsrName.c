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
struct passwd {char* pw_name; } ;
typedef  size_t DWORD ;

/* Variables and functions */
 struct passwd* GetPwByName () ; 
 int /*<<< orphan*/  GetUserName (char*,size_t*) ; 
 int /*<<< orphan*/  Strncpy (char*,char const*,size_t) ; 
 scalar_t__ getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 

void
GetUsrName(char *dst, size_t size)
{
#if defined(WIN32) || defined(_WINDOWS)
	DWORD size1;

	size1 = size - 1;
	if (! GetUserName(dst, &size1))
		(void) strncpy(dst, "unknown", size);
	dst[size - 1] = '\0';
#else
	const char *cp;
	struct passwd *pw;

	pw = NULL;
#ifdef USE_GETPWUID
	/* Try to use getpwuid(), but if we have to, fall back to getpwnam(). */
	if ((pw = getpwuid(getuid())) == NULL)
		pw = GetPwByName();	/* Oh well, try getpwnam() then. */
#else
	/* Try to use getpwnam(), but if we have to, fall back to getpwuid(). */
	if ((pw = GetPwByName()) == NULL)
		pw = getpwuid(getuid());	/* Try getpwnam() then. */
#endif
	if (pw != NULL)
		cp = pw->pw_name;
	else if ((cp = (const char *) getenv("LOGNAME")) == NULL)
			cp = "UNKNOWN";
	(void) Strncpy(dst, cp, size);
#endif
}