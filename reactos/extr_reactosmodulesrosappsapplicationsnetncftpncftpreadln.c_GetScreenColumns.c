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
 int atoi (char*) ; 
 int gScreenColumns ; 
 scalar_t__ getenv (char*) ; 

void
GetScreenColumns(void)
{
#if defined(WIN32) || defined(_WINDOWS)
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
		gScreenColumns = (int) csbi.dwSize.X;
		if (gScreenColumns < 80)
			gScreenColumns = 80;
	}
#else	/* Unix */
#ifdef BINDIR
	char ncftpbookmarks[256];
	FILE *infp;
	vsigproc_t osigpipe;
	int columns;
#endif	/* BINDIR */
	char *cp;

	if ((cp = (char *) getenv("COLUMNS")) == NULL) {
		gScreenColumns = 80;
	} else {
		gScreenColumns = atoi(cp);
		return;
	}

#ifdef TIOCGWINSZ
	{
		struct winsize felix;

		memset(&felix, 0, sizeof(felix));
		if (ioctl(0, TIOCGWINSZ, &felix) == 0) {
			columns = felix.ws_col;
			if ((columns > 0) && (columns < GL_BUF_SIZE))
				gScreenColumns = columns;
			else
				gScreenColumns = 80;
			return;
		}
	}
#endif

#ifdef BINDIR
	/* Don't run things as root unless really necessary. */
	if (gUid == 0)
		return;

	/* This is a brutal hack where we've hacked a
	 * special command line option into ncftp_bookmarks
	 * (which is linked with curses) so that it computes
	 * the screen size and prints it to stdout.
	 *
	 * This function runs ncftp_bookmarks and gets
	 * that information.  The reason we do this is that
	 * we may or may not have a sane installation of
	 * curses/termcap, and we don't want to increase
	 * NcFTP's complexity by the curses junk just to
	 * get the screen size.  Instead, we delegate this
	 * to ncftp_bookmarks which already deals with the
	 * ugliness of curses.
	 */

	STRNCPY(ncftpbookmarks, BINDIR);
	STRNCAT(ncftpbookmarks, "/");
	STRNCAT(ncftpbookmarks, "ncftpbookmarks");

	if (access(ncftpbookmarks, X_OK) < 0)
		return;

	STRNCAT(ncftpbookmarks, " --dimensions-terse");

	osigpipe = NcSignal(SIGPIPE, SIG_IGN);
	infp = popen(ncftpbookmarks, "r");
	if (infp != NULL) {
		columns = 0;
		(void) fscanf(infp, "%d", &columns);
		while (getc(infp) != EOF) {}
		(void) pclose(infp);

		if ((columns > 0) && (columns < GL_BUF_SIZE))
			gScreenColumns = columns;
	}
	(void) NcSignal(SIGPIPE, (sigproc_t) osigpipe);
#endif	/* BINDIR */
#endif	/* Windows */
}