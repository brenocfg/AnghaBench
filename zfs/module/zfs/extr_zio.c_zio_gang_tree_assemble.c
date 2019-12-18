#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  io_bookmark; int /*<<< orphan*/  io_priority; int /*<<< orphan*/  io_spa; struct TYPE_10__* io_gang_leader; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_11__ {int /*<<< orphan*/  gn_gbh; } ;
typedef  TYPE_2__ zio_gang_node_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_IS_GANG (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPA_GANGBLOCKSIZE ; 
 int /*<<< orphan*/  ZIO_GANG_CHILD_FLAGS (TYPE_1__*) ; 
 int /*<<< orphan*/ * abd_get_from_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zio_gang_node_alloc (TYPE_2__**) ; 
 int /*<<< orphan*/  zio_gang_tree_assemble_done ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_read (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zio_gang_tree_assemble(zio_t *gio, blkptr_t *bp, zio_gang_node_t **gnpp)
{
	zio_gang_node_t *gn = zio_gang_node_alloc(gnpp);
	abd_t *gbh_abd = abd_get_from_buf(gn->gn_gbh, SPA_GANGBLOCKSIZE);

	ASSERT(gio->io_gang_leader == gio);
	ASSERT(BP_IS_GANG(bp));

	zio_nowait(zio_read(gio, gio->io_spa, bp, gbh_abd, SPA_GANGBLOCKSIZE,
	    zio_gang_tree_assemble_done, gn, gio->io_priority,
	    ZIO_GANG_CHILD_FLAGS(gio), &gio->io_bookmark));
}