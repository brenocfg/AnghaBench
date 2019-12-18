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
typedef  scalar_t__ zfs_keyformat_t ;
typedef  char uint8_t ;
struct termios {int c_lflag; } ;
struct sigaction {int /*<<< orphan*/  sa_handler; int /*<<< orphan*/  sa_mask; scalar_t__ sa_flags; } ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ECHO ; 
 int ECHOE ; 
 int ECHOK ; 
 int ECHONL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int WRAPPING_KEY_LEN ; 
 scalar_t__ ZFS_KEYFORMAT_RAW ; 
 int /*<<< orphan*/  catch_signal ; 
 scalar_t__ caught_interrupt ; 
 int errno ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_format_prompt_string (scalar_t__) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ isatty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,scalar_t__) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,struct sigaction*) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static int
get_key_material_raw(FILE *fd, const char *fsname, zfs_keyformat_t keyformat,
    boolean_t again, boolean_t newkey, uint8_t **buf, size_t *len_out)
{
	int ret = 0, bytes;
	size_t buflen = 0;
	struct termios old_term, new_term;
	struct sigaction act, osigint, osigtstp;

	*len_out = 0;

	if (isatty(fileno(fd))) {
		/*
		 * handle SIGINT and ignore SIGSTP. This is necessary to
		 * restore the state of the terminal.
		 */
		caught_interrupt = 0;
		act.sa_flags = 0;
		(void) sigemptyset(&act.sa_mask);
		act.sa_handler = catch_signal;

		(void) sigaction(SIGINT, &act, &osigint);
		act.sa_handler = SIG_IGN;
		(void) sigaction(SIGTSTP, &act, &osigtstp);

		/* prompt for the key */
		if (fsname != NULL) {
			(void) printf("%s %s%s for '%s': ",
			    (again) ? "Re-enter" : "Enter",
			    (newkey) ? "new " : "",
			    get_format_prompt_string(keyformat), fsname);
		} else {
			(void) printf("%s %s%s: ",
			    (again) ? "Re-enter" : "Enter",
			    (newkey) ? "new " : "",
			    get_format_prompt_string(keyformat));

		}
		(void) fflush(stdout);

		/* disable the terminal echo for key input */
		(void) tcgetattr(fileno(fd), &old_term);

		new_term = old_term;
		new_term.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);

		ret = tcsetattr(fileno(fd), TCSAFLUSH, &new_term);
		if (ret != 0) {
			ret = errno;
			errno = 0;
			goto out;
		}
	}

	/* read the key material */
	if (keyformat != ZFS_KEYFORMAT_RAW) {
		bytes = getline((char **)buf, &buflen, fd);
		if (bytes < 0) {
			ret = errno;
			errno = 0;
			goto out;
		}

		/* trim the ending newline if it exists */
		if ((*buf)[bytes - 1] == '\n') {
			(*buf)[bytes - 1] = '\0';
			bytes--;
		}
	} else {
		/*
		 * Raw keys may have newline characters in them and so can't
		 * use getline(). Here we attempt to read 33 bytes so that we
		 * can properly check the key length (the file should only have
		 * 32 bytes).
		 */
		*buf = malloc((WRAPPING_KEY_LEN + 1) * sizeof (char));
		if (*buf == NULL) {
			ret = ENOMEM;
			goto out;
		}

		bytes = fread(*buf, 1, WRAPPING_KEY_LEN + 1, fd);
		if (bytes < 0) {
			/* size errors are handled by the calling function */
			free(*buf);
			*buf = NULL;
			ret = errno;
			errno = 0;
			goto out;
		}
	}

	*len_out = bytes;

out:
	if (isatty(fileno(fd))) {
		/* reset the terminal */
		(void) tcsetattr(fileno(fd), TCSAFLUSH, &old_term);
		(void) sigaction(SIGINT, &osigint, NULL);
		(void) sigaction(SIGTSTP, &osigtstp, NULL);

		/* if we caught a signal, re-throw it now */
		if (caught_interrupt != 0) {
			(void) kill(getpid(), caught_interrupt);
		}

		/* print the newline that was not echo'd */
		printf("\n");
	}

	return (ret);

}