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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOM_ADD (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  ATOM_INC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _memory_block ; 
 int /*<<< orphan*/  _used_memory ; 
 int /*<<< orphan*/ * get_allocated_field (int /*<<< orphan*/ ) ; 

__attribute__((used)) inline static void
update_xmalloc_stat_alloc(uint32_t handle, size_t __n) {
	ATOM_ADD(&_used_memory, __n);
	ATOM_INC(&_memory_block);
	ssize_t* allocated = get_allocated_field(handle);
	if(allocated) {
		ATOM_ADD(allocated, __n);
	}
}