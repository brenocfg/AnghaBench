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
typedef  scalar_t__ uint32_t ;
struct mem_data {scalar_t__ handle; scalar_t__ allocated; } ;

/* Variables and functions */
 int SLOT_SIZE ; 
 struct mem_data* mem_stats ; 
 scalar_t__ skynet_current_handle () ; 

size_t
malloc_current_memory(void) {
	uint32_t handle = skynet_current_handle();
	int i;
	for(i=0; i<SLOT_SIZE; i++) {
		struct mem_data* data = &mem_stats[i];
		if(data->handle == (uint32_t)handle && data->allocated != 0) {
			return (size_t) data->allocated;
		}
	}
	return 0;
}