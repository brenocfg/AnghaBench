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
struct timeval {unsigned long tv_sec; scalar_t__ tv_usec; } ;
typedef  int fd_set ;
struct TYPE_3__ {int ctrlSocketR; int /*<<< orphan*/ * cin; } ;
typedef  TYPE_1__* FTPCIPtr ;

/* Variables and functions */
 int /*<<< orphan*/  FD_SET (int,int*) ; 
 int /*<<< orphan*/  FD_ZERO (int*) ; 
 int SELECT_TYPE_ARG234 ; 
 int fileno (int /*<<< orphan*/ *) ; 
 int select (int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int
WaitResponse(const FTPCIPtr cip, unsigned int sec)
{
	int result;
	fd_set ss;
	struct timeval tv;
	int fd;

#ifdef NO_SIGNALS
	fd = cip->ctrlSocketR;
#else	/* NO_SIGNALS */
	if (cip->cin == NULL)
		return (-1);
	fd = fileno(cip->cin);
#endif	/* NO_SIGNALS */
	if (fd < 0)
		return (-1);
	FD_ZERO(&ss);
	FD_SET(fd, &ss);
	tv.tv_sec = (unsigned long) sec;
	tv.tv_usec = 0;
	result = select(fd + 1, SELECT_TYPE_ARG234 &ss, NULL, NULL, &tv);
	return (result);
}