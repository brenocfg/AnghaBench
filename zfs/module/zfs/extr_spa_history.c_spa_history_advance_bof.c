#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  spa_history; int /*<<< orphan*/ * spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_7__ {int sh_phys_max_off; int sh_pool_create_len; int /*<<< orphan*/  sh_records_lost; int /*<<< orphan*/  sh_bof; } ;
typedef  TYPE_2__ spa_history_phys_t ;
typedef  int /*<<< orphan*/  reclen ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_READ_PREFETCH ; 
 int LE_64 (int) ; 
 int MIN (int,int) ; 
 int dmu_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 
 int spa_history_log_to_phys (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int
spa_history_advance_bof(spa_t *spa, spa_history_phys_t *shpp)
{
	objset_t *mos = spa->spa_meta_objset;
	uint64_t firstread, reclen, phys_bof;
	char buf[sizeof (reclen)];
	int err;

	phys_bof = spa_history_log_to_phys(shpp->sh_bof, shpp);
	firstread = MIN(sizeof (reclen), shpp->sh_phys_max_off - phys_bof);

	if ((err = dmu_read(mos, spa->spa_history, phys_bof, firstread,
	    buf, DMU_READ_PREFETCH)) != 0)
		return (err);
	if (firstread != sizeof (reclen)) {
		if ((err = dmu_read(mos, spa->spa_history,
		    shpp->sh_pool_create_len, sizeof (reclen) - firstread,
		    buf + firstread, DMU_READ_PREFETCH)) != 0)
			return (err);
	}

	reclen = LE_64(*((uint64_t *)buf));
	shpp->sh_bof += reclen + sizeof (reclen);
	shpp->sh_records_lost++;
	return (0);
}