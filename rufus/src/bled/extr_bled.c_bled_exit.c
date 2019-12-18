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
 int /*<<< orphan*/ * bled_cancel_request ; 
 int bled_initialized ; 
 int /*<<< orphan*/ * bled_printf ; 
 int /*<<< orphan*/ * bled_progress ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * global_crc32_table ; 

void bled_exit(void)
{
	bled_printf = NULL;
	bled_progress = NULL;
	bled_cancel_request = NULL;
	if (global_crc32_table) {
		free(global_crc32_table);
		global_crc32_table = NULL;
	}
	bled_initialized = false;
}