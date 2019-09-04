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
struct TYPE_3__ {int /*<<< orphan*/  reg_size; } ;
typedef  TYPE_1__ bin_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_ALLOC_JUNK ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
arena_alloc_junk_small(void *ptr, const bin_info_t *bin_info, bool zero) {
	if (!zero) {
		memset(ptr, JEMALLOC_ALLOC_JUNK, bin_info->reg_size);
	}
}