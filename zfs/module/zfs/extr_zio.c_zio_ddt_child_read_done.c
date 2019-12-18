#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ io_error; int /*<<< orphan*/  io_lock; int /*<<< orphan*/ * io_abd; TYPE_2__* io_private; int /*<<< orphan*/ * io_bp; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  ddt_phys_t ;
struct TYPE_8__ {int /*<<< orphan*/ * dde_repair_abd; } ;
typedef  TYPE_2__ ddt_entry_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  abd_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_phys_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ddt_phys_select (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* zio_unique_parent (TYPE_1__*) ; 

__attribute__((used)) static void
zio_ddt_child_read_done(zio_t *zio)
{
	blkptr_t *bp = zio->io_bp;
	ddt_entry_t *dde = zio->io_private;
	ddt_phys_t *ddp;
	zio_t *pio = zio_unique_parent(zio);

	mutex_enter(&pio->io_lock);
	ddp = ddt_phys_select(dde, bp);
	if (zio->io_error == 0)
		ddt_phys_clear(ddp);	/* this ddp doesn't need repair */

	if (zio->io_error == 0 && dde->dde_repair_abd == NULL)
		dde->dde_repair_abd = zio->io_abd;
	else
		abd_free(zio->io_abd);
	mutex_exit(&pio->io_lock);
}