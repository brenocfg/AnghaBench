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
typedef  int /*<<< orphan*/  vm_range_recorder_t ;
typedef  int /*<<< orphan*/  vm_address_t ;
typedef  int /*<<< orphan*/  task_t ;
typedef  int /*<<< orphan*/  memory_reader_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 

__attribute__((used)) static kern_return_t
zone_enumerator(task_t task, void *data, unsigned type_mask,
    vm_address_t zone_address, memory_reader_t reader,
    vm_range_recorder_t recorder) {
	return KERN_SUCCESS;
}