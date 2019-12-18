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
struct TYPE_3__ {int /*<<< orphan*/  zpool_name; int /*<<< orphan*/ * zpool_hdl; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 char* dgettext (int /*<<< orphan*/ ,char*) ; 
 int lzc_pool_checkpoint_discard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_standard_error (int /*<<< orphan*/ *,int,char*) ; 

int
zpool_discard_checkpoint(zpool_handle_t *zhp)
{
	libzfs_handle_t *hdl = zhp->zpool_hdl;
	char msg[1024];
	int error;

	error = lzc_pool_checkpoint_discard(zhp->zpool_name);
	if (error != 0) {
		(void) snprintf(msg, sizeof (msg), dgettext(TEXT_DOMAIN,
		    "cannot discard checkpoint in '%s'"), zhp->zpool_name);
		(void) zpool_standard_error(hdl, error, msg);
		return (-1);
	}

	return (0);
}