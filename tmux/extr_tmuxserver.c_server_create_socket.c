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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int ENAMETOOLONG ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int S_IRWXO ; 
 int S_IXGRP ; 
 int S_IXUSR ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_un*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setblocking (int,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_path ; 
 int /*<<< orphan*/  strerror (int) ; 
 size_t strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int umask (int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
server_create_socket(char **cause)
{
	struct sockaddr_un	sa;
	size_t			size;
	mode_t			mask;
	int			fd, saved_errno;

	memset(&sa, 0, sizeof sa);
	sa.sun_family = AF_UNIX;
	size = strlcpy(sa.sun_path, socket_path, sizeof sa.sun_path);
	if (size >= sizeof sa.sun_path) {
		errno = ENAMETOOLONG;
		goto fail;
	}
	unlink(sa.sun_path);

	if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
		goto fail;

	mask = umask(S_IXUSR|S_IXGRP|S_IRWXO);
	if (bind(fd, (struct sockaddr *)&sa, sizeof sa) == -1) {
		saved_errno = errno;
		close(fd);
		errno = saved_errno;
		goto fail;
	}
	umask(mask);

	if (listen(fd, 128) == -1) {
		saved_errno = errno;
		close(fd);
		errno = saved_errno;
		goto fail;
	}
	setblocking(fd, 0);

	return (fd);

fail:
	if (cause != NULL) {
		xasprintf(cause, "error creating %s (%s)", socket_path,
		    strerror(errno));
	}
	return (-1);
}