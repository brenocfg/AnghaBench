#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t io_child_type; scalar_t__* io_child_error; int /*<<< orphan*/  io_pipeline; int /*<<< orphan*/  io_gang_tree; int /*<<< orphan*/  io_abd; struct TYPE_6__* io_gang_leader; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_IS_GANG (int /*<<< orphan*/ *) ; 
 size_t ZIO_CHILD_GANG ; 
 int /*<<< orphan*/  ZIO_CHILD_GANG_BIT ; 
 int /*<<< orphan*/  ZIO_INTERLOCK_PIPELINE ; 
 int /*<<< orphan*/  ZIO_WAIT_DONE ; 
 int /*<<< orphan*/  zio_gang_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_gang_tree_issue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_wait_for_children (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zio_t *
zio_gang_issue(zio_t *zio)
{
	blkptr_t *bp = zio->io_bp;

	if (zio_wait_for_children(zio, ZIO_CHILD_GANG_BIT, ZIO_WAIT_DONE)) {
		return (NULL);
	}

	ASSERT(BP_IS_GANG(bp) && zio->io_gang_leader == zio);
	ASSERT(zio->io_child_type > ZIO_CHILD_GANG);

	if (zio->io_child_error[ZIO_CHILD_GANG] == 0)
		zio_gang_tree_issue(zio, zio->io_gang_tree, bp, zio->io_abd,
		    0);
	else
		zio_gang_tree_free(&zio->io_gang_tree);

	zio->io_pipeline = ZIO_INTERLOCK_PIPELINE;

	return (zio);
}