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
typedef  int /*<<< orphan*/  pwbuf ;

/* Variables and functions */
 int /*<<< orphan*/  FGets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int _getch () ; 
 int /*<<< orphan*/  _isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fputs (char const* const,int /*<<< orphan*/ ) ; 
 char* getpass (char const* const) ; 
 int /*<<< orphan*/  isatty (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 

char *
GetPass(const char *const prompt)
{
#ifdef HAVE_GETPASS
	return getpass(prompt);
#elif defined(_CONSOLE) && (defined(WIN32) || defined(_WINDOWS))
	static char pwbuf[128];
	char *dst, *dlim;
	int c;

	(void) memset(pwbuf, 0, sizeof(pwbuf));
	if (! _isatty(_fileno(stdout)))
		return (pwbuf);
	(void) fputs(prompt, stdout);
	(void) fflush(stdout);

	for (dst = pwbuf, dlim = dst + sizeof(pwbuf) - 1;;) {
		c = _getch();
		if ((c == 0) || (c == 0xe0)) {
			/* The key is a function or arrow key; read and discard. */
			(void) _getch();
		}
		if ((c == '\r') || (c == '\n'))
			break;
		if (dst < dlim)
			*dst++ = c;
	}
	*dst = '\0';

	(void) fflush(stdout);
	(void) fflush(stdin);
	return (pwbuf);
#else
	static char pwbuf[128];

	(void) memset(pwbuf, 0, sizeof(pwbuf));
#if defined(WIN32) || defined(_WINDOWS)
	if (! _isatty(_fileno(stdout)))
#else
	if (! isatty(1))
#endif
		return (pwbuf);
	(void) fputs(prompt, stdout);
	(void) fflush(stdout);
	(void) FGets(pwbuf, sizeof(pwbuf), stdin);
	(void) fflush(stdout);
	(void) fflush(stdin);
	return (pwbuf);
#endif
}