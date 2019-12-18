#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* dp_scan; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int boolean_t ;
struct TYPE_5__ {scalar_t__ scn_func; } ;
struct TYPE_7__ {TYPE_1__ scn_phys; } ;

/* Variables and functions */
 scalar_t__ POOL_SCAN_RESILVER ; 
 scalar_t__ dsl_scan_is_running (TYPE_4__*) ; 

boolean_t
dsl_scan_resilvering(dsl_pool_t *dp)
{
	return (dsl_scan_is_running(dp->dp_scan) &&
	    dp->dp_scan->scn_phys.scn_func == POOL_SCAN_RESILVER);
}