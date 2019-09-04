#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int errNo; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int kErrSetLinger ; 

int
SetLinger(const FTPCIPtr cip, int sockfd, int onoff)
{
#ifndef SO_LINGER
	cip->errNo = kErrSetLinger;
	return (kErrSetLinger);
#else
	struct linger li;

	if (onoff != 0) {
		li.l_onoff = 1;
		li.l_linger = 120;	/* 2 minutes, but system ignores field. */
	} else {
		li.l_onoff = 0;
		li.l_linger = 0;
	}
	/* Have the system make an effort to deliver any unsent data,
	 * even after we close the connection.
	 */
	if (setsockopt(sockfd, SOL_SOCKET, SO_LINGER, (char *) &li, (int) sizeof(li)) < 0) {
		/* Error(cip, kDoPerror, "Could not set linger mode.\n"); */
		cip->errNo = kErrSetLinger;
		return (kErrSetLinger);
	}
	return (kNoErr);
#endif	/* SO_LINGER */
}