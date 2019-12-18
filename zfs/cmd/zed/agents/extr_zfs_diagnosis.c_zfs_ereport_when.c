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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  void* int64_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
struct TYPE_3__ {void* ertv_nsec; void* ertv_sec; } ;
typedef  TYPE_1__ er_timeval_t ;

/* Variables and functions */
 int /*<<< orphan*/  FM_EREPORT_TIME ; 
 void* UINT64_MAX ; 
 scalar_t__ nvlist_lookup_int64_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void***,int*) ; 

__attribute__((used)) static void
zfs_ereport_when(fmd_hdl_t *hdl, nvlist_t *nvl, er_timeval_t *when)
{
	int64_t *tod;
	uint_t	nelem;

	if (nvlist_lookup_int64_array(nvl, FM_EREPORT_TIME, &tod,
	    &nelem) == 0 && nelem == 2) {
		when->ertv_sec = tod[0];
		when->ertv_nsec = tod[1];
	} else {
		when->ertv_sec = when->ertv_nsec = UINT64_MAX;
	}
}