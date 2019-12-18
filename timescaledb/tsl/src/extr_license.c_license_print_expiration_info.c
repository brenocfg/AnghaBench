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
struct TYPE_2__ {int /*<<< orphan*/  end_time; scalar_t__ enterprise_features_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_WARNING ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  TIMESTAMP_NOT_FINITE (int /*<<< orphan*/ ) ; 
 TYPE_1__ current_license ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  license_print_expiration_warning_if_needed () ; 
 int printed_license_expiration_warning ; 
 int /*<<< orphan*/  timestamptz_out ; 

void
license_print_expiration_info(void)
{
	if (!TIMESTAMP_NOT_FINITE(current_license.end_time) &&
		current_license.enterprise_features_enabled)
	{
		ereport(NOTICE,
				(errcode(ERRCODE_WARNING),
				 errmsg("your Timescale Enterprise License expires on %s",
						DatumGetCString(
							DirectFunctionCall1(timestamptz_out, current_license.end_time)))));
	}

	else
	{
		printed_license_expiration_warning = false;
		license_print_expiration_warning_if_needed();
	}
}