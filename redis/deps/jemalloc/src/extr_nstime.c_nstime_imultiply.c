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
typedef  int uint64_t ;
struct TYPE_3__ {int ns; } ;
typedef  TYPE_1__ nstime_t ;

/* Variables and functions */
 int UINT64_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

void
nstime_imultiply(nstime_t *time, uint64_t multiplier) {
	assert((((time->ns | multiplier) & (UINT64_MAX << (sizeof(uint64_t) <<
	    2))) == 0) || ((time->ns * multiplier) / multiplier == time->ns));

	time->ns *= multiplier;
}