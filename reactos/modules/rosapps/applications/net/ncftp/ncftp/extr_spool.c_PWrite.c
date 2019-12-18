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

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ write (int,char const*,int) ; 

__attribute__((used)) static int
PWrite(int sfd, const char *const buf0, size_t size)
{
	int nleft;
	const char *buf = buf0;
	int nwrote;

	nleft = (int) size;
	for (;;) {
		nwrote = (int) write(sfd, buf, nleft);
		if (nwrote < 0) {
			if (errno != EINTR) {
				nwrote = (int) size - nleft;
				if (nwrote == 0)
					nwrote = -1;
				return (nwrote);
			} else {
				errno = 0;
				nwrote = 0;
				/* Try again. */
			}
		}
		nleft -= nwrote;
		if (nleft <= 0)
			break;
		buf += nwrote;
	}
	nwrote = (int) size - nleft;
	return (nwrote);
}