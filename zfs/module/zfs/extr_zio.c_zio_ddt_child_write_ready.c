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
struct TYPE_7__ {int zp_copies; } ;
struct TYPE_8__ {int /*<<< orphan*/  io_txg; int /*<<< orphan*/  io_bp; scalar_t__ io_error; TYPE_3__* io_private; int /*<<< orphan*/  io_spa; TYPE_1__ io_prop; } ;
typedef  TYPE_2__ zio_t ;
typedef  int /*<<< orphan*/  zio_link_t ;
typedef  int /*<<< orphan*/  ddt_t ;
typedef  int /*<<< orphan*/  ddt_phys_t ;
struct TYPE_9__ {TYPE_2__** dde_lead_zio; int /*<<< orphan*/ * dde_phys; } ;
typedef  TYPE_3__ ddt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ddt_bp_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ddt_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ddt_phys_fill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ddt_select (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* zio_walk_parents (TYPE_2__*,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void
zio_ddt_child_write_ready(zio_t *zio)
{
	int p = zio->io_prop.zp_copies;
	ddt_t *ddt = ddt_select(zio->io_spa, zio->io_bp);
	ddt_entry_t *dde = zio->io_private;
	ddt_phys_t *ddp = &dde->dde_phys[p];
	zio_t *pio;

	if (zio->io_error)
		return;

	ddt_enter(ddt);

	ASSERT(dde->dde_lead_zio[p] == zio);

	ddt_phys_fill(ddp, zio->io_bp);

	zio_link_t *zl = NULL;
	while ((pio = zio_walk_parents(zio, &zl)) != NULL)
		ddt_bp_fill(ddp, pio->io_bp, zio->io_txg);

	ddt_exit(ddt);
}