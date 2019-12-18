#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zko_kobj; struct TYPE_8__* zko_children; } ;
typedef  TYPE_2__ zfs_mod_kobj_t ;
struct TYPE_9__ {int p2k_attr_count; int /*<<< orphan*/  p2k_show_func; TYPE_1__* p2k_table; TYPE_2__* p2k_parent; } ;
typedef  TYPE_3__ prop_to_kobj_arg_t ;
struct TYPE_7__ {char* pd_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (char const*) ; 
 int ZPROP_CONT ; 
 int zfs_kobj_add (TYPE_2__*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  zfs_kobj_add_attr (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int zfs_kobj_init (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_kobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zprop_attrs ; 

__attribute__((used)) static int
zprop_to_kobj(int prop, void *args)
{
	prop_to_kobj_arg_t *data = args;
	zfs_mod_kobj_t *parent = data->p2k_parent;
	zfs_mod_kobj_t *zfs_kobj = &parent->zko_children[prop];
	const char *name = data->p2k_table[prop].pd_name;
	int err;

	ASSERT(name);

	err = zfs_kobj_init(zfs_kobj, data->p2k_attr_count, 0,
	    data->p2k_show_func);
	if (err)
		return (ZPROP_CONT);

	for (int i = 0; i < data->p2k_attr_count; i++)
		zfs_kobj_add_attr(zfs_kobj, i, zprop_attrs[i]);

	err = zfs_kobj_add(zfs_kobj, &parent->zko_kobj, name);
	if (err)
		zfs_kobj_release(&zfs_kobj->zko_kobj);

	return (ZPROP_CONT);
}