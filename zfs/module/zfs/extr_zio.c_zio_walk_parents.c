#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  io_parent_list; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_10__ {TYPE_1__* zl_parent; TYPE_1__* zl_child; } ;
typedef  TYPE_2__ zio_link_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 

zio_t *
zio_walk_parents(zio_t *cio, zio_link_t **zl)
{
	list_t *pl = &cio->io_parent_list;

	*zl = (*zl == NULL) ? list_head(pl) : list_next(pl, *zl);
	if (*zl == NULL)
		return (NULL);

	ASSERT((*zl)->zl_child == cio);
	return ((*zl)->zl_parent);
}