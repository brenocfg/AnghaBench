#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* zv_name; int /*<<< orphan*/  zv_state_lock; } ;
typedef  TYPE_1__ zvol_state_t ;
struct TYPE_9__ {int /*<<< orphan*/  (* zv_rename_minor ) (TYPE_1__*,char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 char* kmem_asprintf (char*,char const*,char,char*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_4__* ops ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,char*) ; 
 scalar_t__ zvol_inhibit_dev ; 
 int /*<<< orphan*/  zvol_state_list ; 
 int /*<<< orphan*/  zvol_state_lock ; 

__attribute__((used)) static void
zvol_rename_minors_impl(const char *oldname, const char *newname)
{
	zvol_state_t *zv, *zv_next;
	int oldnamelen, newnamelen;

	if (zvol_inhibit_dev)
		return;

	oldnamelen = strlen(oldname);
	newnamelen = strlen(newname);

	rw_enter(&zvol_state_lock, RW_READER);

	for (zv = list_head(&zvol_state_list); zv != NULL; zv = zv_next) {
		zv_next = list_next(&zvol_state_list, zv);

		mutex_enter(&zv->zv_state_lock);

		if (strcmp(zv->zv_name, oldname) == 0) {
			ops->zv_rename_minor(zv, newname);
		} else if (strncmp(zv->zv_name, oldname, oldnamelen) == 0 &&
		    (zv->zv_name[oldnamelen] == '/' ||
		    zv->zv_name[oldnamelen] == '@')) {
			char *name = kmem_asprintf("%s%c%s", newname,
			    zv->zv_name[oldnamelen],
			    zv->zv_name + oldnamelen + 1);
			ops->zv_rename_minor(zv, name);
			kmem_strfree(name);
		}

		mutex_exit(&zv->zv_state_lock);
	}

	rw_exit(&zvol_state_lock);
}