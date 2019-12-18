#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ scn_state; } ;
struct TYPE_5__ {TYPE_1__ scn_phys; } ;
typedef  TYPE_2__ dsl_scan_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ DSS_SCANNING ; 

__attribute__((used)) static inline boolean_t
dsl_scan_is_running(const dsl_scan_t *scn)
{
	return (scn->scn_phys.scn_state == DSS_SCANNING);
}