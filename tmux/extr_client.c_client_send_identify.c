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
typedef  char pid_t ;

/* Variables and functions */
 size_t IMSG_HEADER_SIZE ; 
 size_t MAX_IMSGSIZE ; 
 int /*<<< orphan*/  MSG_IDENTIFY_CLIENTPID ; 
 int /*<<< orphan*/  MSG_IDENTIFY_CWD ; 
 int /*<<< orphan*/  MSG_IDENTIFY_DONE ; 
 int /*<<< orphan*/  MSG_IDENTIFY_ENVIRON ; 
 int /*<<< orphan*/  MSG_IDENTIFY_FLAGS ; 
 int /*<<< orphan*/  MSG_IDENTIFY_STDIN ; 
 int /*<<< orphan*/  MSG_IDENTIFY_TERM ; 
 int /*<<< orphan*/  MSG_IDENTIFY_TTYNAME ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int client_flags ; 
 int /*<<< orphan*/  client_peer ; 
 int dup (int /*<<< orphan*/ ) ; 
 char** environ ; 
 int /*<<< orphan*/  fatal (char*) ; 
 char* getenv (char*) ; 
 char getpid () ; 
 int /*<<< orphan*/  proc_send (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,...) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void
client_send_identify(const char *ttynam, const char *cwd)
{
	const char	 *s;
	char		**ss;
	size_t		  sslen;
	int		  fd, flags = client_flags;
	pid_t		  pid;

	proc_send(client_peer, MSG_IDENTIFY_FLAGS, -1, &flags, sizeof flags);

	if ((s = getenv("TERM")) == NULL)
		s = "";
	proc_send(client_peer, MSG_IDENTIFY_TERM, -1, s, strlen(s) + 1);

	proc_send(client_peer, MSG_IDENTIFY_TTYNAME, -1, ttynam,
	    strlen(ttynam) + 1);
	proc_send(client_peer, MSG_IDENTIFY_CWD, -1, cwd, strlen(cwd) + 1);

	if ((fd = dup(STDIN_FILENO)) == -1)
		fatal("dup failed");
	proc_send(client_peer, MSG_IDENTIFY_STDIN, fd, NULL, 0);

	pid = getpid();
	proc_send(client_peer, MSG_IDENTIFY_CLIENTPID, -1, &pid, sizeof pid);

	for (ss = environ; *ss != NULL; ss++) {
		sslen = strlen(*ss) + 1;
		if (sslen > MAX_IMSGSIZE - IMSG_HEADER_SIZE)
			continue;
		proc_send(client_peer, MSG_IDENTIFY_ENVIRON, -1, *ss, sslen);
	}

	proc_send(client_peer, MSG_IDENTIFY_DONE, -1, NULL, 0);
}