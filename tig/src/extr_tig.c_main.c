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
struct view {int /*<<< orphan*/  keymap; } ;
typedef  enum request { ____Placeholder_request } request ;
struct TYPE_2__ {int /*<<< orphan*/ * git_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODESET ; 
 char* ENCODING_UTF8 ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ ICONV_NONE ; 
 int /*<<< orphan*/  ICONV_TRANSLIT ; 
 int /*<<< orphan*/  LC_ALL ; 
 int REQ_NONE ; 
#define  REQ_PROMPT 129 
#define  REQ_UNKNOWN 128 
 int /*<<< orphan*/  REQ_VIEW_HELP ; 
 int REQ_VIEW_PAGER ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGSEGV ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int SIZEOF_STR ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 size_t current_view ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  die_if_failed (int /*<<< orphan*/ ,char*) ; 
 struct view** display ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_view_key (struct view*,int /*<<< orphan*/ ) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  handle_git_prefix () ; 
 int /*<<< orphan*/  hangup_children ; 
 scalar_t__ iconv_open (char const*,char*) ; 
 int /*<<< orphan*/  init_display () ; 
 int /*<<< orphan*/  init_tty () ; 
 int /*<<< orphan*/  isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_git_config () ; 
 int /*<<< orphan*/  load_options () ; 
 int /*<<< orphan*/  load_refs (int) ; 
 int /*<<< orphan*/  load_repo_info () ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int open_pager_mode (int) ; 
 int open_prompt (struct view*) ; 
 scalar_t__ opt_iconv_out ; 
 int parse_options (int,char const**,int) ; 
 int /*<<< orphan*/  prompt_init () ; 
 int read_key_combo (int /*<<< orphan*/ ) ; 
 TYPE_1__ repo ; 
 int /*<<< orphan*/  report (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_prompt_command (int /*<<< orphan*/ *,char const**) ; 
 scalar_t__ setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sighup_handler ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigsegv_handler ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ string_format (char*,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ view_driver (struct view*,int) ; 

int
main(int argc, const char *argv[])
{
	const char *codeset = ENCODING_UTF8;
	bool pager_mode = !isatty(STDIN_FILENO);
	enum request request = parse_options(argc, argv, pager_mode);
	struct view *view;

	init_tty();

	atexit(hangup_children);

	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		die("Failed to setup signal handler");

	if (signal(SIGHUP, sighup_handler) == SIG_ERR)
		die("Failed to setup signal handler");

#ifdef DEBUG
	if (signal(SIGSEGV, sigsegv_handler) == SIG_ERR)
		die("Failed to setup signal handler");
#endif

	if (setlocale(LC_ALL, "")) {
		codeset = nl_langinfo(CODESET);
	}

	die_if_failed(handle_git_prefix(), "Failed to handle GIT_PREFIX");
	die_if_failed(load_repo_info(), "Failed to load repo info.");
	die_if_failed(load_options(), "Failed to load user config.");
	die_if_failed(load_git_config(), "Failed to load repo config.");

	prompt_init();

	/* Require a git repository unless when running in pager mode. */
	if (!repo.git_dir[0] && request != REQ_VIEW_PAGER)
		die("Not a git repository");

	if (codeset && strcmp(codeset, ENCODING_UTF8)) {
		char translit[SIZEOF_STR];

		if (string_format(translit, "%s%s", codeset, ICONV_TRANSLIT))
			opt_iconv_out = iconv_open(translit, ENCODING_UTF8);
		else
			opt_iconv_out = iconv_open(codeset, ENCODING_UTF8);
		if (opt_iconv_out == ICONV_NONE)
			die("Failed to initialize character set conversion");
	}

	die_if_failed(load_refs(false), "Failed to load refs.");

	init_display();

	if (pager_mode)
		request = open_pager_mode(request);

	if (getenv("TIG_SCRIPT")) {
		const char *script_command[] = { "script", getenv("TIG_SCRIPT"), NULL };

		run_prompt_command(NULL, script_command);
	}

	while (view_driver(display[current_view], request)) {
		view = display[current_view];
		request = read_key_combo(view->keymap);

		/* Some low-level request handling. This keeps access to
		 * status_win restricted. */
		switch (request) {
		case REQ_UNKNOWN:
			report("Unknown key, press %s for help",
			       get_view_key(view, REQ_VIEW_HELP));
			request = REQ_NONE;
			break;
		case REQ_PROMPT:
			request = open_prompt(view);
			break;
		default:
			break;
		}
	}

	exit(EXIT_SUCCESS);

	return 0;
}