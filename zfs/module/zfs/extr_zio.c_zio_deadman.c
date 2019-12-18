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
struct TYPE_4__ {int /*<<< orphan*/ * io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
#define  ZIO_FAILURE_MODE_CONTINUE 130 
#define  ZIO_FAILURE_MODE_PANIC 129 
#define  ZIO_FAILURE_MODE_WAIT 128 
 int /*<<< orphan*/  fm_panic (char*,char*,char*) ; 
 int spa_get_deadman_failmode (int /*<<< orphan*/ *) ; 
 char* spa_name (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_suspended (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_deadman_enabled ; 
 int /*<<< orphan*/  zio_deadman_impl (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
zio_deadman(zio_t *pio, char *tag)
{
	spa_t *spa = pio->io_spa;
	char *name = spa_name(spa);

	if (!zfs_deadman_enabled || spa_suspended(spa))
		return;

	zio_deadman_impl(pio, 0);

	switch (spa_get_deadman_failmode(spa)) {
	case ZIO_FAILURE_MODE_WAIT:
		zfs_dbgmsg("%s waiting for hung I/O to pool '%s'", tag, name);
		break;

	case ZIO_FAILURE_MODE_CONTINUE:
		zfs_dbgmsg("%s restarting hung I/O for pool '%s'", tag, name);
		break;

	case ZIO_FAILURE_MODE_PANIC:
		fm_panic("%s determined I/O to pool '%s' is hung.", tag, name);
		break;
	}
}