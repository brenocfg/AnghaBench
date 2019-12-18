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
struct TYPE_2__ {int fd; } ;
struct imsgbuf {int fd; int /*<<< orphan*/  fds; int /*<<< orphan*/  pid; TYPE_1__ w; int /*<<< orphan*/  r; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msgbuf_init (TYPE_1__*) ; 

void
imsg_init(struct imsgbuf *ibuf, int fd)
{
	msgbuf_init(&ibuf->w);
	memset(&ibuf->r, 0, sizeof(ibuf->r));
	ibuf->fd = fd;
	ibuf->w.fd = fd;
	ibuf->pid = getpid();
	TAILQ_INIT(&ibuf->fds);
}