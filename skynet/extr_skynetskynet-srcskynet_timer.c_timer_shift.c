#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
struct timer {int time; } ;

/* Variables and functions */
 int TIME_LEVEL_MASK ; 
 int TIME_LEVEL_SHIFT ; 
 int TIME_NEAR ; 
 int TIME_NEAR_SHIFT ; 
 int /*<<< orphan*/  move_list (struct timer*,int,int) ; 

__attribute__((used)) static void
timer_shift(struct timer *T) {
	int mask = TIME_NEAR;
	uint32_t ct = ++T->time;
	if (ct == 0) {
		move_list(T, 3, 0);
	} else {
		uint32_t time = ct >> TIME_NEAR_SHIFT;
		int i=0;

		while ((ct & (mask-1))==0) {
			int idx=time & TIME_LEVEL_MASK;
			if (idx!=0) {
				move_list(T, i, idx);
				break;				
			}
			mask <<= TIME_LEVEL_SHIFT;
			time >>= TIME_LEVEL_SHIFT;
			++i;
		}
	}
}