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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 scalar_t__ recv (int,char*,size_t,int /*<<< orphan*/ ) ; 

ssize_t
_nc_recvn(int sd, void *vptr, size_t n)
{
	size_t nleft;
	ssize_t	nrecv;
	char *ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
        nrecv = recv(sd, ptr, nleft, 0);
        if (nrecv < 0) {
            if (errno == EINTR) {
                continue;
            }
            return nrecv;
        }
        if (nrecv == 0) {
            break;
        }

        nleft -= (size_t)nrecv;
        ptr += nrecv;
    }

    return (ssize_t)(n - nleft);
}