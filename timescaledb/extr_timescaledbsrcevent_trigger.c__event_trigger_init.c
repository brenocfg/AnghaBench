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
 int /*<<< orphan*/  ddl_commands_fmgrinfo ; 
 int /*<<< orphan*/  dropped_objects_fmgrinfo ; 
 int /*<<< orphan*/  fmgr_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmgr_internal_function (char*) ; 

void
_event_trigger_init(void)
{
	fmgr_info(fmgr_internal_function("pg_event_trigger_ddl_commands"), &ddl_commands_fmgrinfo);
	fmgr_info(fmgr_internal_function("pg_event_trigger_dropped_objects"),
			  &dropped_objects_fmgrinfo);
}