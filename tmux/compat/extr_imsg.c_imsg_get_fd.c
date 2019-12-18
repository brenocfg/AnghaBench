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
struct imsgbuf {int /*<<< orphan*/  fds; } ;
struct imsg_fd {int fd; } ;

/* Variables and functions */
 struct imsg_fd* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct imsg_fd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct imsg_fd*) ; 

__attribute__((used)) static int
imsg_get_fd(struct imsgbuf *ibuf)
{
	int		 fd;
	struct imsg_fd	*ifd;

	if ((ifd = TAILQ_FIRST(&ibuf->fds)) == NULL)
		return (-1);

	fd = ifd->fd;
	TAILQ_REMOVE(&ibuf->fds, ifd, entry);
	free(ifd);

	return (fd);
}