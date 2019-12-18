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

/* Variables and functions */
 size_t PAGE ; 
 size_t do_get_size_impl (char*,unsigned int) ; 

__attribute__((used)) static size_t
do_get_active(unsigned arena_ind) {
	return do_get_size_impl("stats.arenas.0.pactive", arena_ind) * PAGE;
}