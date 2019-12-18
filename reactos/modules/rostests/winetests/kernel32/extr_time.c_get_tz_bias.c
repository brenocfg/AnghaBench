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
struct TYPE_3__ {int /*<<< orphan*/  StandardBias; int /*<<< orphan*/  DaylightBias; int /*<<< orphan*/  DaylightDate; int /*<<< orphan*/  StandardDate; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  int /*<<< orphan*/  LONG ;
typedef  int DWORD ;

/* Variables and functions */
#define  TIME_ZONE_ID_DAYLIGHT 130 
#define  TIME_ZONE_ID_STANDARD 129 
#define  TIME_ZONE_ID_UNKNOWN 128 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  trace (char*,int) ; 

__attribute__((used)) static LONG get_tz_bias(const TIME_ZONE_INFORMATION *tzinfo, DWORD tz_id)
{
    switch (tz_id)
    {
    case TIME_ZONE_ID_DAYLIGHT:
        if (memcmp(&tzinfo->StandardDate, &tzinfo->DaylightDate, sizeof(tzinfo->DaylightDate)) != 0)
            return tzinfo->DaylightBias;
        /* fall through */

    case TIME_ZONE_ID_STANDARD:
        return tzinfo->StandardBias;

    default:
        trace("unknown time zone id %d\n", tz_id);
        /* fall through */
    case TIME_ZONE_ID_UNKNOWN:
        return 0;
    }
}