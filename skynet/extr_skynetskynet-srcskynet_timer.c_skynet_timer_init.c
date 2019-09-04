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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  current_point; int /*<<< orphan*/  current; int /*<<< orphan*/  starttime; } ;

/* Variables and functions */
 TYPE_1__* TI ; 
 int /*<<< orphan*/  gettime () ; 
 int /*<<< orphan*/  systime (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* timer_create_timer () ; 

void 
skynet_timer_init(void) {
	TI = timer_create_timer();
	uint32_t current = 0;
	systime(&TI->starttime, &current);
	TI->current = current;
	TI->current_point = gettime();
}