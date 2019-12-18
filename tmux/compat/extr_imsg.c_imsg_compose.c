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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct imsgbuf {int dummy; } ;
struct ibuf {int fd; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int imsg_add (struct ibuf*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imsg_close (struct imsgbuf*,struct ibuf*) ; 
 struct ibuf* imsg_create (struct imsgbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
imsg_compose(struct imsgbuf *ibuf, uint32_t type, uint32_t peerid, pid_t pid,
    int fd, const void *data, uint16_t datalen)
{
	struct ibuf	*wbuf;

	if ((wbuf = imsg_create(ibuf, type, peerid, pid, datalen)) == NULL)
		return (-1);

	if (imsg_add(wbuf, data, datalen) == -1)
		return (-1);

	wbuf->fd = fd;

	imsg_close(ibuf, wbuf);

	return (1);
}