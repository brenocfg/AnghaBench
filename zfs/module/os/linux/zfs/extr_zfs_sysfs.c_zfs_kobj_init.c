#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  release; TYPE_1__* sysfs_ops; int /*<<< orphan*/ * default_attrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  show; } ;
struct TYPE_7__ {int zko_attr_count; int zko_child_count; TYPE_2__ zko_kobj_type; TYPE_1__ zko_sysfs_ops; int /*<<< orphan*/ * zko_attr_list; int /*<<< orphan*/ * zko_default_attrs; int /*<<< orphan*/ * zko_children; } ;
typedef  TYPE_3__ zfs_mod_kobj_t ;
typedef  int /*<<< orphan*/  sysfs_show_func ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_TABLE_SIZE (int) ; 
 int /*<<< orphan*/  CHILD_TABLE_SIZE (int) ; 
 int /*<<< orphan*/  DEFAULT_ATTR_SIZE (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* kmem_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_kobj_release ; 

__attribute__((used)) static int
zfs_kobj_init(zfs_mod_kobj_t *zkobj, int attr_cnt, int child_cnt,
    sysfs_show_func show_func)
{
	/*
	 * Initialize object's attributes. Count can be zero.
	 */
	if (attr_cnt > 0) {
		zkobj->zko_attr_list = kmem_zalloc(ATTR_TABLE_SIZE(attr_cnt),
		    KM_SLEEP);
		if (zkobj->zko_attr_list == NULL)
			return (ENOMEM);
	}
	/* this will always have at least one slot for NULL termination */
	zkobj->zko_default_attrs = kmem_zalloc(DEFAULT_ATTR_SIZE(attr_cnt),
	    KM_SLEEP);
	if (zkobj->zko_default_attrs == NULL) {
		if (zkobj->zko_attr_list != NULL) {
			kmem_free(zkobj->zko_attr_list,
			    ATTR_TABLE_SIZE(attr_cnt));
		}
		return (ENOMEM);
	}
	zkobj->zko_attr_count = attr_cnt;
	zkobj->zko_kobj_type.default_attrs = zkobj->zko_default_attrs;

	if (child_cnt > 0) {
		zkobj->zko_children = kmem_zalloc(CHILD_TABLE_SIZE(child_cnt),
		    KM_SLEEP);
		if (zkobj->zko_children == NULL) {
			if (zkobj->zko_default_attrs != NULL) {
				kmem_free(zkobj->zko_default_attrs,
				    DEFAULT_ATTR_SIZE(attr_cnt));
			}
			if (zkobj->zko_attr_list != NULL) {
				kmem_free(zkobj->zko_attr_list,
				    ATTR_TABLE_SIZE(attr_cnt));
			}
			return (ENOMEM);
		}
		zkobj->zko_child_count = child_cnt;
	}

	zkobj->zko_sysfs_ops.show = show_func;
	zkobj->zko_kobj_type.sysfs_ops = &zkobj->zko_sysfs_ops;
	zkobj->zko_kobj_type.release = zfs_kobj_release;

	return (0);
}