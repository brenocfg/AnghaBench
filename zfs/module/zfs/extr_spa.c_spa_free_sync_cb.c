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
struct TYPE_3__ {int /*<<< orphan*/  io_flags; int /*<<< orphan*/  io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  blkptr_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_free_sync (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spa_free_sync_cb(void *arg, const blkptr_t *bp, dmu_tx_t *tx)
{
	zio_t *zio = arg;

	zio_nowait(zio_free_sync(zio, zio->io_spa, dmu_tx_get_txg(tx), bp,
	    zio->io_flags));
	return (0);
}