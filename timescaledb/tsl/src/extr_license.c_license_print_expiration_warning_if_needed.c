#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_5__ {int /*<<< orphan*/  end_time; } ;
struct TYPE_4__ {int day; } ;
typedef  TYPE_1__ Interval ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetCString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DatumGetTimestampTz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_WARNING ; 
 int /*<<< orphan*/  GetCurrentTransactionStartTimestamp () ; 
 int /*<<< orphan*/  IntervalPGetDatum (TYPE_1__*) ; 
 int /*<<< orphan*/  TimestampTzGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARNING ; 
 TYPE_2__ current_license ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 scalar_t__ license_is_expired () ; 
 int printed_license_expiration_warning ; 
 scalar_t__ timestamp_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timestamptz_mi_interval ; 
 int /*<<< orphan*/  timestamptz_out ; 

void
license_print_expiration_warning_if_needed(void)
{
	if (printed_license_expiration_warning)
		return;

	printed_license_expiration_warning = true;

	if (license_is_expired())
		ereport(WARNING,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("Timescale License expired"),
				 errhint("Your license expired on %s. Renew your license to continue using "
						 "enterprise features.",
						 DatumGetCString(
							 DirectFunctionCall1(timestamptz_out,
												 TimestampTzGetDatum(current_license.end_time))))));
	else
	{
		Interval week = {
			.day = 7,
		};
		TimestampTz warn_after =
			DatumGetTimestampTz(DirectFunctionCall2(timestamptz_mi_interval,
													TimestampTzGetDatum(current_license.end_time),
													IntervalPGetDatum(&week)));

		if (timestamp_cmp_internal(GetCurrentTransactionStartTimestamp(), warn_after) >= 0)
			ereport(WARNING,
					(errcode(ERRCODE_WARNING),
					 errmsg("your Timescale Enterprise License expires on %s",
							DatumGetCString(DirectFunctionCall1(timestamptz_out,
																TimestampTzGetDatum(
																	current_license.end_time))))));
	}
}