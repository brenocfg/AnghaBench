#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* tsl_license_on_assign ) (char const*,void*) ;int /*<<< orphan*/  (* module_shutdown_hook ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CharGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ TS_LICENSE_IS_APACHE_ONLY (char const*) ; 
 int /*<<< orphan*/  TS_LICENSE_TYPE_IS_VALID (char const*) ; 
 int /*<<< orphan*/  can_load ; 
 int /*<<< orphan*/  current_license_can_downgrade_to_apache () ; 
 void* revalidate_license (char const*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (char const*,void*) ; 
 TYPE_1__* ts_cm_functions ; 
 int /*<<< orphan*/ * tsl_handle ; 
 int /*<<< orphan*/ * tsl_startup_fn ; 

void
ts_license_on_assign(const char *newval, void *extra)
{
	if (!can_load)
		return;

	Assert(newval != NULL);
	Assert(TS_LICENSE_TYPE_IS_VALID(newval));
	if (TS_LICENSE_IS_APACHE_ONLY(newval))
	{
		Assert(current_license_can_downgrade_to_apache());
		Assert(extra == NULL);
		if (ts_cm_functions->module_shutdown_hook != NULL)
			ts_cm_functions->module_shutdown_hook();
		return;
	}

	Assert(tsl_handle != NULL);
	Assert(tsl_startup_fn != NULL);
	DirectFunctionCall1(tsl_startup_fn, CharGetDatum(0));
#ifdef WIN32
	Assert(extra == NULL);
	extra = revalidate_license(newval);
#endif
	Assert(extra != NULL);
	ts_cm_functions->tsl_license_on_assign(newval, extra);
}