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
typedef  int /*<<< orphan*/  TimestampTz ;
struct TYPE_3__ {int /*<<< orphan*/  end_time; } ;
typedef  TYPE_1__ LicenseInfo ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTransactionStartTimestamp () ; 
 scalar_t__ timestamp_cmp_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool
license_info_is_expired(const LicenseInfo *license)
{
	TimestampTz current_time = GetCurrentTransactionStartTimestamp();

	return timestamp_cmp_internal(license->end_time, current_time) < 0;
}