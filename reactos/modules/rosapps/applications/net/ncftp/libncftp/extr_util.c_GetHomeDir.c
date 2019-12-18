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
struct passwd {char* pw_dir; } ;

/* Variables and functions */
 struct passwd* GetPwByName () ; 
 int /*<<< orphan*/  Strncat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  Strncpy (char*,char const*,size_t) ; 
 char* getenv (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getuid () ; 

void
GetHomeDir(char *dst, size_t size)
{
#if defined(WIN32) || defined(_WINDOWS)
	const char *homedrive, *homepath;

	homedrive = getenv("HOMEDRIVE");
	homepath = getenv("HOMEPATH");
	if ((homedrive != NULL) && (homepath != NULL)) {
		(void) Strncpy(dst, homedrive, size);
		(void) Strncat(dst, homepath, size);
		return;
	}

//	GetSpecialDir(dst, size, CSIDL_PERSONAL	/* "My Documents" */);
//	if (dst[0] != '\0')
//		return;
//
//	dst[0] = '\0';
//	if (GetWindowsDirectory(dst, size - 1) < 1)
//		(void) Strncpy(dst, ".", size);
//	else if (dst[1] == ':') {
//		dst[2] = '\\';
//		dst[3] = '\0';
//	}
#else
	const char *cp;
	struct passwd *pw;

	pw = NULL;
#if defined(USE_GETPWUID)
	/* Try to use getpwuid(), but if we have to, fall back to getpwnam(). */
	if ((pw = getpwuid(getuid())) == NULL)
		pw = GetPwByName();	/* Oh well, try getpwnam() then. */
#else
	/* Try to use getpwnam(), but if we have to, fall back to getpwuid(). */
	if ((pw = GetPwByName()) == NULL)
		pw = getpwuid(getuid());	/* Try getpwnam() then. */
#endif
	if (pw != NULL)
		cp = pw->pw_dir;
	else if ((cp = (const char *) getenv("LOGNAME")) == NULL)
			cp = ".";
	(void) Strncpy(dst, cp, size);
#endif
}