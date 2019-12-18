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
struct TYPE_3__ {int /*<<< orphan*/  zap_dbuf; int /*<<< orphan*/  zap_rwlock; } ;
typedef  TYPE_1__ zap_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 scalar_t__ RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_will_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rw_tryupgrade (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zap_tryupgradedir(zap_t *zap, dmu_tx_t *tx)
{
	if (RW_WRITE_HELD(&zap->zap_rwlock))
		return (1);
	if (rw_tryupgrade(&zap->zap_rwlock)) {
		dmu_buf_will_dirty(zap->zap_dbuf, tx);
		return (1);
	}
	return (0);
}