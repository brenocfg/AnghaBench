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
typedef  char winsize ;
struct termios {int dummy; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  I_PUSH ; 
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TIOCSCTTY ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int /*<<< orphan*/  TTY_NAME_MAX ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fork () ; 
 scalar_t__ grantpt (int) ; 
 int ioctl (int,int /*<<< orphan*/ ,char*) ; 
 int open (char*,int) ; 
 char* ptsname (int) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 
 scalar_t__ unlockpt (int) ; 

pid_t
forkpty(int *master, char *name, struct termios *tio, struct winsize *ws)
{
	int	slave = -1;
	char   *path;
	pid_t	pid;

	if ((*master = open("/dev/ptmx", O_RDWR|O_NOCTTY)) == -1)
		return (-1);
	if (grantpt(*master) != 0)
		goto out;
	if (unlockpt(*master) != 0)
		goto out;

	if ((path = ptsname(*master)) == NULL)
		goto out;
	if (name != NULL)
		strlcpy(name, path, TTY_NAME_MAX);
	if ((slave = open(path, O_RDWR|O_NOCTTY)) == -1)
		goto out;

	switch (pid = fork()) {
	case -1:
		goto out;
	case 0:
		close(*master);

		setsid();
#ifdef TIOCSCTTY
		if (ioctl(slave, TIOCSCTTY, NULL) == -1)
			fatal("ioctl failed");
#endif

		if (ioctl(slave, I_PUSH, "ptem") == -1)
			fatal("ioctl failed");
		if (ioctl(slave, I_PUSH, "ldterm") == -1)
			fatal("ioctl failed");

		if (tio != NULL && tcsetattr(slave, TCSAFLUSH, tio) == -1)
			fatal("tcsetattr failed");
		if (ioctl(slave, TIOCSWINSZ, ws) == -1)
			fatal("ioctl failed");

		dup2(slave, 0);
		dup2(slave, 1);
		dup2(slave, 2);
		if (slave > 2)
			close(slave);
		return (0);
	}

	close(slave);
	return (pid);

out:
	if (*master != -1)
		close(*master);
	if (slave != -1)
		close(slave);
	return (-1);
}