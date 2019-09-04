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
struct sockaddr_un {int /*<<< orphan*/  sun_path; int /*<<< orphan*/  sun_family; } ;
struct sockaddr {int dummy; } ;
struct event_base {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 scalar_t__ ECONNREFUSED ; 
 scalar_t__ ENAMETOOLONG ; 
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int client_get_lock (char*) ; 
 int /*<<< orphan*/  client_proc ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int server_start (int /*<<< orphan*/ ,struct event_base*,int,char*) ; 
 int /*<<< orphan*/  setblocking (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strerror (scalar_t__) ; 
 size_t strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ unlink (char const*) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*) ; 

__attribute__((used)) static int
client_connect(struct event_base *base, const char *path, int start_server)
{
	struct sockaddr_un	sa;
	size_t			size;
	int			fd, lockfd = -1, locked = 0;
	char		       *lockfile = NULL;

	memset(&sa, 0, sizeof sa);
	sa.sun_family = AF_UNIX;
	size = strlcpy(sa.sun_path, path, sizeof sa.sun_path);
	if (size >= sizeof sa.sun_path) {
		errno = ENAMETOOLONG;
		return (-1);
	}
	log_debug("socket is %s", path);

retry:
	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		return (-1);

	log_debug("trying connect");
	if (connect(fd, (struct sockaddr *)&sa, sizeof sa) == -1) {
		log_debug("connect failed: %s", strerror(errno));
		if (errno != ECONNREFUSED && errno != ENOENT)
			goto failed;
		if (!start_server)
			goto failed;
		close(fd);

		if (!locked) {
			xasprintf(&lockfile, "%s.lock", path);
			if ((lockfd = client_get_lock(lockfile)) < 0) {
				log_debug("didn't get lock (%d)", lockfd);

				free(lockfile);
				lockfile = NULL;

				if (lockfd == -2)
					goto retry;
			}
			log_debug("got lock (%d)", lockfd);

			/*
			 * Always retry at least once, even if we got the lock,
			 * because another client could have taken the lock,
			 * started the server and released the lock between our
			 * connect() and flock().
			 */
			locked = 1;
			goto retry;
		}

		if (lockfd >= 0 && unlink(path) != 0 && errno != ENOENT) {
			free(lockfile);
			close(lockfd);
			return (-1);
		}
		fd = server_start(client_proc, base, lockfd, lockfile);
	}

	if (locked && lockfd >= 0) {
		free(lockfile);
		close(lockfd);
	}
	setblocking(fd, 0);
	return (fd);

failed:
	if (locked) {
		free(lockfile);
		close(lockfd);
	}
	close(fd);
	return (-1);
}