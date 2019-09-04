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
struct mevent {int /*<<< orphan*/  me_param; int /*<<< orphan*/  me_type; int /*<<< orphan*/  me_fd; int /*<<< orphan*/  (* me_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct kevent {struct mevent* udata; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mevent_handle(struct kevent *kev, int numev)
{
	struct mevent *mevp;
	int i;

	for (i = 0; i < numev; i++) {
		mevp = kev[i].udata;

		/* XXX check for EV_ERROR ? */

		(*mevp->me_func)(mevp->me_fd, mevp->me_type, mevp->me_param);
	}
}