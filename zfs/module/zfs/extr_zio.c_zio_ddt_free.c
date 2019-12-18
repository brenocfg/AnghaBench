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
struct TYPE_4__ {scalar_t__ io_child_type; int /*<<< orphan*/ * io_bp; int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  ddt_t ;
typedef  int /*<<< orphan*/  ddt_phys_t ;
typedef  int /*<<< orphan*/  ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int BP_GET_DEDUP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ ZIO_CHILD_LOGICAL ; 
 int /*<<< orphan*/  ddt_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ddt_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddt_phys_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ddt_phys_select (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ddt_select (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * freedde ; 

__attribute__((used)) static zio_t *
zio_ddt_free(zio_t *zio)
{
	spa_t *spa = zio->io_spa;
	blkptr_t *bp = zio->io_bp;
	ddt_t *ddt = ddt_select(spa, bp);
	ddt_entry_t *dde;
	ddt_phys_t *ddp;

	ASSERT(BP_GET_DEDUP(bp));
	ASSERT(zio->io_child_type == ZIO_CHILD_LOGICAL);

	ddt_enter(ddt);
	freedde = dde = ddt_lookup(ddt, bp, B_TRUE);
	if (dde) {
		ddp = ddt_phys_select(dde, bp);
		if (ddp)
			ddt_phys_decref(ddp);
	}
	ddt_exit(ddt);

	return (zio);
}