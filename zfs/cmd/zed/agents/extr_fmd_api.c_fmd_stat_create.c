#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  fmd_stat_t ;
struct TYPE_2__ {scalar_t__ mod_ustat_cnt; int /*<<< orphan*/ * mod_ustat; } ;
typedef  TYPE_1__ fmd_module_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 scalar_t__ FMD_STAT_NOALLOC ; 

fmd_stat_t *
fmd_stat_create(fmd_hdl_t *hdl, uint_t flags, uint_t nstats, fmd_stat_t *statv)
{
	fmd_module_t *mp = (fmd_module_t *)hdl;

	if (flags == FMD_STAT_NOALLOC) {
		mp->mod_ustat = statv;
		mp->mod_ustat_cnt = nstats;
	}

	return (statv);
}