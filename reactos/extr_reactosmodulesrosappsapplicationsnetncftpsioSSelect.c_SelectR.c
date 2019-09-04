#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fds; int timeout; int /*<<< orphan*/  maxfd; } ;
typedef  TYPE_1__* SelectSetPtr ;
typedef  int /*<<< orphan*/  SelectSet ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int SELECT_TYPE_ARG234 ; 
 int SELECT_TYPE_ARG5 ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int select (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
SelectR(SelectSetPtr ssp, SelectSetPtr resultssp)
{
	int rc;

	do {
		memcpy(resultssp, ssp, sizeof(SelectSet));
		rc = select(resultssp->maxfd, SELECT_TYPE_ARG234 &resultssp->fds, NULL, NULL, SELECT_TYPE_ARG5 &resultssp->timeout);
	} while ((rc < 0) && (errno == EINTR));
	return (rc);
}