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
typedef  int /*<<< orphan*/  spa_iostats_t ;
struct TYPE_3__ {int /*<<< orphan*/  ks_data; } ;
typedef  TYPE_1__ kstat_t ;

/* Variables and functions */
 int KSTAT_WRITE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spa_iostats_template ; 

int
spa_iostats_update(kstat_t *ksp, int rw)
{
	if (rw == KSTAT_WRITE) {
		memcpy(ksp->ks_data, &spa_iostats_template,
		    sizeof (spa_iostats_t));
	}

	return (0);
}