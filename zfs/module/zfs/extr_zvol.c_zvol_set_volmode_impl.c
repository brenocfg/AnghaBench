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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  fstrans_cookie_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* zv_create_minor ) (char*) ;} ;

/* Variables and functions */
#define  ZFS_VOLMODE_DEFAULT 131 
#define  ZFS_VOLMODE_DEV 130 
#define  ZFS_VOLMODE_GEOM 129 
#define  ZFS_VOLMODE_NONE 128 
 TYPE_1__* ops ; 
 int /*<<< orphan*/  spl_fstrans_mark () ; 
 int /*<<< orphan*/  spl_fstrans_unmark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char*,char) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  stub2 (char*) ; 
 int /*<<< orphan*/  zvol_remove_minor_impl (char*) ; 
 int const zvol_volmode ; 

__attribute__((used)) static void
zvol_set_volmode_impl(char *name, uint64_t volmode)
{
	fstrans_cookie_t cookie = spl_fstrans_mark();

	if (strchr(name, '@') != NULL)
		return;

	/*
	 * It's unfortunate we need to remove minors before we create new ones:
	 * this is necessary because our backing gendisk (zvol_state->zv_disk)
	 * coule be different when we set, for instance, volmode from "geom"
	 * to "dev" (or vice versa).
	 * A possible optimization is to modify our consumers so we don't get
	 * called when "volmode" does not change.
	 */
	switch (volmode) {
		case ZFS_VOLMODE_NONE:
			(void) zvol_remove_minor_impl(name);
			break;
		case ZFS_VOLMODE_GEOM:
		case ZFS_VOLMODE_DEV:
			(void) zvol_remove_minor_impl(name);
			(void) ops->zv_create_minor(name);
			break;
		case ZFS_VOLMODE_DEFAULT:
			(void) zvol_remove_minor_impl(name);
			if (zvol_volmode == ZFS_VOLMODE_NONE)
				break;
			else /* if zvol_volmode is invalid defaults to "geom" */
				(void) ops->zv_create_minor(name);
			break;
	}

	spl_fstrans_unmark(cookie);
}