#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zprop_func ) (int,void*) ;
struct TYPE_7__ {int pd_propnum; scalar_t__ pd_zfs_mod_supported; scalar_t__ pd_visible; } ;
typedef  TYPE_1__ zprop_desc_t ;
typedef  int /*<<< orphan*/  zfs_type_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int ZPROP_CONT ; 
 int /*<<< orphan*/  free (TYPE_1__**) ; 
 TYPE_1__** kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__**,int) ; 
 TYPE_1__** malloc (int) ; 
 int /*<<< orphan*/  qsort (void*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zprop_compare ; 
 int zprop_get_numprops (int /*<<< orphan*/ ) ; 
 TYPE_1__* zprop_get_proptable (int /*<<< orphan*/ ) ; 

int
zprop_iter_common(zprop_func func, void *cb, boolean_t show_all,
    boolean_t ordered, zfs_type_t type)
{
	int i, num_props, size, prop;
	zprop_desc_t *prop_tbl;
	zprop_desc_t **order;

	prop_tbl = zprop_get_proptable(type);
	num_props = zprop_get_numprops(type);
	size = num_props * sizeof (zprop_desc_t *);

#if defined(_KERNEL)
	order = kmem_alloc(size, KM_SLEEP);
#else
	if ((order = malloc(size)) == NULL)
		return (ZPROP_CONT);
#endif

	for (int j = 0; j < num_props; j++)
		order[j] = &prop_tbl[j];

	if (ordered) {
		qsort((void *)order, num_props, sizeof (zprop_desc_t *),
		    zprop_compare);
	}

	prop = ZPROP_CONT;
	for (i = 0; i < num_props; i++) {
		if ((order[i]->pd_visible || show_all) &&
		    order[i]->pd_zfs_mod_supported &&
		    (func(order[i]->pd_propnum, cb) != ZPROP_CONT)) {
			prop = order[i]->pd_propnum;
			break;
		}
	}

#if defined(_KERNEL)
	kmem_free(order, size);
#else
	free(order);
#endif
	return (prop);
}