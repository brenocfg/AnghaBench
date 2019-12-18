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
struct TYPE_4__ {struct TYPE_4__* sc_user_prop; struct TYPE_4__* sc_next; } ;
typedef  TYPE_1__ zfs_sort_column_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 

void
zfs_free_sort_columns(zfs_sort_column_t *sc)
{
	zfs_sort_column_t *col;

	while (sc != NULL) {
		col = sc->sc_next;
		free(sc->sc_user_prop);
		free(sc);
		sc = col;
	}
}