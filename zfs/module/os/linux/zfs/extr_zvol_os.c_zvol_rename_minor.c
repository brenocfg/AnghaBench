#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* zv_zso; int /*<<< orphan*/  zv_hash; int /*<<< orphan*/  zv_hlink; int /*<<< orphan*/  zv_name; int /*<<< orphan*/  zv_state_lock; } ;
typedef  TYPE_2__ zvol_state_t ;
struct TYPE_4__ {int /*<<< orphan*/  zvo_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVOL_HT_HEAD (int /*<<< orphan*/ ) ; 
 int get_disk_ro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_disk_ro (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  zvol_name_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_state_lock ; 

__attribute__((used)) static void
zvol_rename_minor(zvol_state_t *zv, const char *newname)
{
	int readonly = get_disk_ro(zv->zv_zso->zvo_disk);

	ASSERT(RW_LOCK_HELD(&zvol_state_lock));
	ASSERT(MUTEX_HELD(&zv->zv_state_lock));

	strlcpy(zv->zv_name, newname, sizeof (zv->zv_name));

	/* move to new hashtable entry  */
	zv->zv_hash = zvol_name_hash(zv->zv_name);
	hlist_del(&zv->zv_hlink);
	hlist_add_head(&zv->zv_hlink, ZVOL_HT_HEAD(zv->zv_hash));

	/*
	 * The block device's read-only state is briefly changed causing
	 * a KOBJ_CHANGE uevent to be issued.  This ensures udev detects
	 * the name change and fixes the symlinks.  This does not change
	 * ZVOL_RDONLY in zv->zv_flags so the actual read-only state never
	 * changes.  This would normally be done using kobject_uevent() but
	 * that is a GPL-only symbol which is why we need this workaround.
	 */
	set_disk_ro(zv->zv_zso->zvo_disk, !readonly);
	set_disk_ro(zv->zv_zso->zvo_disk, readonly);
}