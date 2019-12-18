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
struct options_table_entry {int scope; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int CLIENT_256COLOURS ; 
 int CLIENT_CONTROL ; 
 int CLIENT_CONTROLCONTROL ; 
 int CLIENT_LOGIN ; 
 int CLIENT_UTF8 ; 
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 int /*<<< orphan*/  LC_TIME ; 
 int MODEKEY_EMACS ; 
 int MODEKEY_VI ; 
 int OPTIONS_TABLE_SERVER ; 
 int OPTIONS_TABLE_SESSION ; 
 int OPTIONS_TABLE_WINDOW ; 
 char* VERSION ; 
 int client_main (int /*<<< orphan*/ ,int,char**,int) ; 
 char** environ ; 
 int /*<<< orphan*/  environ_create () ; 
 int /*<<< orphan*/  environ_put (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  environ_set (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 char* find_cwd () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* getenv (char*) ; 
 int getopt (int,char**,char*) ; 
 char* getprogname () ; 
 int getptmfd () ; 
 char* getshell () ; 
 int /*<<< orphan*/  global_environ ; 
 int /*<<< orphan*/  global_options ; 
 int /*<<< orphan*/  global_s_options ; 
 int /*<<< orphan*/  global_w_options ; 
 int /*<<< orphan*/  log_add_level () ; 
 char* make_label (char*,char**) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 char const* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  options_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  options_default (int /*<<< orphan*/ ,struct options_table_entry const*) ; 
 int /*<<< orphan*/  options_set_number (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  options_set_string (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char const*) ; 
 struct options_table_entry* options_table ; 
 int /*<<< orphan*/  osdep_event_init () ; 
 scalar_t__ pledge (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int ptm_fd ; 
 int /*<<< orphan*/  set_cfg_file (char const*) ; 
 int /*<<< orphan*/ * setlocale (int /*<<< orphan*/ ,char*) ; 
 char const* shell_command ; 
 char* socket_path ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/ * strcasestr (char const*,char*) ; 
 size_t strcspn (char*,char*) ; 
 char* strrchr (char const*,char) ; 
 int /*<<< orphan*/ * strstr (char const*,char*) ; 
 int /*<<< orphan*/  tzset () ; 
 int /*<<< orphan*/  usage () ; 
 char* xstrdup (char const*) ; 

int
main(int argc, char **argv)
{
	char					*path, *label, *cause, **var;
	const char				*s, *shell, *cwd;
	int					 opt, flags, keys;
	const struct options_table_entry	*oe;

	if (setlocale(LC_CTYPE, "en_US.UTF-8") == NULL &&
	    setlocale(LC_CTYPE, "C.UTF-8") == NULL) {
		if (setlocale(LC_CTYPE, "") == NULL)
			errx(1, "invalid LC_ALL, LC_CTYPE or LANG");
		s = nl_langinfo(CODESET);
		if (strcasecmp(s, "UTF-8") != 0 && strcasecmp(s, "UTF8") != 0)
			errx(1, "need UTF-8 locale (LC_CTYPE) but have %s", s);
	}

	setlocale(LC_TIME, "");
	tzset();

	if (**argv == '-')
		flags = CLIENT_LOGIN;
	else
		flags = 0;

	label = path = NULL;
	while ((opt = getopt(argc, argv, "2c:Cdf:lL:qS:uUVv")) != -1) {
		switch (opt) {
		case '2':
			flags |= CLIENT_256COLOURS;
			break;
		case 'c':
			shell_command = optarg;
			break;
		case 'C':
			if (flags & CLIENT_CONTROL)
				flags |= CLIENT_CONTROLCONTROL;
			else
				flags |= CLIENT_CONTROL;
			break;
		case 'V':
			printf("%s %s\n", getprogname(), VERSION);
			exit(0);
		case 'f':
			set_cfg_file(optarg);
			break;
		case 'l':
			flags |= CLIENT_LOGIN;
			break;
		case 'L':
			free(label);
			label = xstrdup(optarg);
			break;
		case 'q':
			break;
		case 'S':
			free(path);
			path = xstrdup(optarg);
			break;
		case 'u':
			flags |= CLIENT_UTF8;
			break;
		case 'v':
			log_add_level();
			break;
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (shell_command != NULL && argc != 0)
		usage();

	if ((ptm_fd = getptmfd()) == -1)
		err(1, "getptmfd");
	if (pledge("stdio rpath wpath cpath flock fattr unix getpw sendfd "
	    "recvfd proc exec tty ps", NULL) != 0)
		err(1, "pledge");

	/*
	 * tmux is a UTF-8 terminal, so if TMUX is set, assume UTF-8.
	 * Otherwise, if the user has set LC_ALL, LC_CTYPE or LANG to contain
	 * UTF-8, it is a safe assumption that either they are using a UTF-8
	 * terminal, or if not they know that output from UTF-8-capable
	 * programs may be wrong.
	 */
	if (getenv("TMUX") != NULL)
		flags |= CLIENT_UTF8;
	else {
		s = getenv("LC_ALL");
		if (s == NULL || *s == '\0')
			s = getenv("LC_CTYPE");
		if (s == NULL || *s == '\0')
			s = getenv("LANG");
		if (s == NULL || *s == '\0')
			s = "";
		if (strcasestr(s, "UTF-8") != NULL ||
		    strcasestr(s, "UTF8") != NULL)
			flags |= CLIENT_UTF8;
	}

	global_environ = environ_create();
	for (var = environ; *var != NULL; var++)
		environ_put(global_environ, *var);
	if ((cwd = find_cwd()) != NULL)
		environ_set(global_environ, "PWD", "%s", cwd);

	global_options = options_create(NULL);
	global_s_options = options_create(NULL);
	global_w_options = options_create(NULL);
	for (oe = options_table; oe->name != NULL; oe++) {
		if (oe->scope & OPTIONS_TABLE_SERVER)
			options_default(global_options, oe);
		if (oe->scope & OPTIONS_TABLE_SESSION)
			options_default(global_s_options, oe);
		if (oe->scope & OPTIONS_TABLE_WINDOW)
			options_default(global_w_options, oe);
	}

	/*
	 * The default shell comes from SHELL or from the user's passwd entry
	 * if available.
	 */
	shell = getshell();
	options_set_string(global_s_options, "default-shell", 0, "%s", shell);

	/* Override keys to vi if VISUAL or EDITOR are set. */
	if ((s = getenv("VISUAL")) != NULL || (s = getenv("EDITOR")) != NULL) {
		if (strrchr(s, '/') != NULL)
			s = strrchr(s, '/') + 1;
		if (strstr(s, "vi") != NULL)
			keys = MODEKEY_VI;
		else
			keys = MODEKEY_EMACS;
		options_set_number(global_s_options, "status-keys", keys);
		options_set_number(global_w_options, "mode-keys", keys);
	}

	/*
	 * If socket is specified on the command-line with -S or -L, it is
	 * used. Otherwise, $TMUX is checked and if that fails "default" is
	 * used.
	 */
	if (path == NULL && label == NULL) {
		s = getenv("TMUX");
		if (s != NULL && *s != '\0' && *s != ',') {
			path = xstrdup(s);
			path[strcspn(path, ",")] = '\0';
		}
	}
	if (path == NULL && (path = make_label(label, &cause)) == NULL) {
		if (cause != NULL) {
			fprintf(stderr, "%s\n", cause);
			free(cause);
		}
		exit(1);
	}
	socket_path = path;
	free(label);

	/* Pass control to the client. */
	exit(client_main(osdep_event_init(), argc, argv, flags));
}