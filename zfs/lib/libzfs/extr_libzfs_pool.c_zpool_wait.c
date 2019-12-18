#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_wait_activity_t ;
struct TYPE_4__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/  zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zpool_standard_error_fmt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zpool_wait_status (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

int
zpool_wait(zpool_handle_t *zhp, zpool_wait_activity_t activity)
{
	boolean_t missing;

	int error = zpool_wait_status(zhp, activity, &missing, NULL);

	if (missing) {
		(void) zpool_standard_error_fmt(zhp->zpool_hdl, ENOENT,
		    dgettext(TEXT_DOMAIN, "error waiting in pool '%s'"),
		    zhp->zpool_name);
		return (ENOENT);
	} else {
		return (error);
	}
}