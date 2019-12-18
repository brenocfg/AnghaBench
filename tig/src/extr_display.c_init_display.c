#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_STATUS ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TABSIZE ; 
 scalar_t__ atexit (int /*<<< orphan*/ ) ; 
 int cursed ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  done_display ; 
 int /*<<< orphan*/  enable_mouse (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  get_line_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  getmaxyx (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  init_colors () ; 
 int /*<<< orphan*/  initscr () ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  keypad (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  newterm (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  newwin (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_mouse ; 
 int /*<<< orphan*/  opt_tab_size ; 
 TYPE_1__ opt_tty ; 
 int /*<<< orphan*/  set_tabsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_terminal_modes () ; 
 int /*<<< orphan*/  status_win ; 
 int /*<<< orphan*/  stdscr ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int use_scroll_redrawwin ; 
 int use_scroll_status_wclear ; 
 int /*<<< orphan*/  wbkgdset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
init_display(void)
{
	bool no_display = !!getenv("TIG_NO_DISPLAY");
	const char *term;
	int x, y;

	if (!opt_tty.file)
		die("Can't initialize display without tty");

	if (atexit(done_display))
		die("Failed to register done_display");

	/* Initialize the curses library */
	if (!no_display && isatty(STDIN_FILENO)) {
		/* Needed for ncurses 5.4 compatibility. */
		cursed = !!initscr();
	} else {
		/* Leave stdin and stdout alone when acting as a pager. */
		FILE *out_tty;

		out_tty = no_display ? fopen("/dev/null", "w+") : opt_tty.file;
		if (!out_tty)
			die("Failed to open tty for output");
		cursed = !!newterm(NULL, out_tty, opt_tty.file);
	}

	if (!cursed)
		die("Failed to initialize curses");

	set_terminal_modes();
	init_colors();

	getmaxyx(stdscr, y, x);
	status_win = newwin(1, x, y - 1, 0);
	if (!status_win)
		die("Failed to create status window");

	/* Enable keyboard mapping */
	keypad(status_win, true);
	wbkgdset(status_win, get_line_attr(NULL, LINE_STATUS));
	enable_mouse(opt_mouse);

#if defined(NCURSES_VERSION_PATCH) && (NCURSES_VERSION_PATCH >= 20080119)
	set_tabsize(opt_tab_size);
#else
	TABSIZE = opt_tab_size;
#endif

	term = getenv("XTERM_VERSION")
		   ? NULL
		   : (getenv("TERM_PROGRAM") ? getenv("TERM_PROGRAM") : getenv("COLORTERM"));
	if (term && !strcmp(term, "gnome-terminal")) {
		/* In the gnome-terminal-emulator, the warning message
		 * shown when scrolling up one line while the cursor is
		 * on the first line followed by scrolling down one line
		 * corrupts the status line. This is fixed by calling
		 * wclear. */
		use_scroll_status_wclear = true;
		use_scroll_redrawwin = false;

	} else if (term &&
			   (!strcmp(term, "xrvt-xpm") || !strcmp(term, "Apple_Terminal") ||
				!strcmp(term, "iTerm.app"))) {
		/* No problems with full optimizations in
		 * xrvt-(unicode)
		 * aterm
		 * Terminal.app
		 * iTerm2 */
		use_scroll_status_wclear = use_scroll_redrawwin = false;

	} else {
		/* When scrolling in (u)xterm the last line in the
		 * scrolling direction will update slowly.  This is
		 * the conservative default. */
		use_scroll_redrawwin = true;
		use_scroll_status_wclear = false;
	}
}