#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  spa_history; int /*<<< orphan*/  spa_history_lock; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_9__ {int sh_phys_max_off; int sh_pool_create_len; int sh_eof; int sh_bof; } ;
typedef  TYPE_2__ spa_history_phys_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ *) ; 
 int spa_history_advance_bof (TYPE_1__*,TYPE_2__*) ; 
 int spa_history_log_to_phys (int,TYPE_2__*) ; 

__attribute__((used)) static int
spa_history_write(spa_t *spa, void *buf, uint64_t len, spa_history_phys_t *shpp,
    dmu_tx_t *tx)
{
	uint64_t firstwrite, phys_eof;
	objset_t *mos = spa->spa_meta_objset;
	int err;

	ASSERT(MUTEX_HELD(&spa->spa_history_lock));

	/* see if we need to reset logical BOF */
	while (shpp->sh_phys_max_off - shpp->sh_pool_create_len -
	    (shpp->sh_eof - shpp->sh_bof) <= len) {
		if ((err = spa_history_advance_bof(spa, shpp)) != 0) {
			return (err);
		}
	}

	phys_eof = spa_history_log_to_phys(shpp->sh_eof, shpp);
	firstwrite = MIN(len, shpp->sh_phys_max_off - phys_eof);
	shpp->sh_eof += len;
	dmu_write(mos, spa->spa_history, phys_eof, firstwrite, buf, tx);

	len -= firstwrite;
	if (len > 0) {
		/* write out the rest at the beginning of physical file */
		dmu_write(mos, spa->spa_history, shpp->sh_pool_create_len,
		    len, (char *)buf + firstwrite, tx);
	}

	return (0);
}