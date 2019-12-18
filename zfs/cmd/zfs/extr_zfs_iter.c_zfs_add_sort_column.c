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
struct TYPE_3__ {struct TYPE_3__* sc_last; struct TYPE_3__* sc_next; void* sc_user_prop; int /*<<< orphan*/  sc_reverse; scalar_t__ sc_prop; } ;
typedef  TYPE_1__ zfs_sort_column_t ;
typedef  scalar_t__ zfs_prop_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ ZPROP_INVAL ; 
 void* safe_malloc (int) ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ zfs_name_to_prop (char const*) ; 
 int /*<<< orphan*/  zfs_prop_user (char const*) ; 

int
zfs_add_sort_column(zfs_sort_column_t **sc, const char *name,
    boolean_t reverse)
{
	zfs_sort_column_t *col;
	zfs_prop_t prop;

	if ((prop = zfs_name_to_prop(name)) == ZPROP_INVAL &&
	    !zfs_prop_user(name))
		return (-1);

	col = safe_malloc(sizeof (zfs_sort_column_t));

	col->sc_prop = prop;
	col->sc_reverse = reverse;
	if (prop == ZPROP_INVAL) {
		col->sc_user_prop = safe_malloc(strlen(name) + 1);
		(void) strcpy(col->sc_user_prop, name);
	}

	if (*sc == NULL) {
		col->sc_last = col;
		*sc = col;
	} else {
		(*sc)->sc_last->sc_next = col;
		(*sc)->sc_last = col;
	}

	return (0);
}