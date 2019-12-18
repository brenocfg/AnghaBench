#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ Bias; scalar_t__* StandardName; scalar_t__ StandardBias; scalar_t__* DaylightName; scalar_t__* TimeZoneKeyName; int /*<<< orphan*/  DaylightDate; int /*<<< orphan*/  StandardDate; } ;
struct TYPE_5__ {scalar_t__ Bias; scalar_t__* StandardName; scalar_t__ StandardBias; scalar_t__* DaylightName; int /*<<< orphan*/  DaylightDate; int /*<<< orphan*/  StandardDate; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  TYPE_2__ DYNAMIC_TIME_ZONE_INFORMATION ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetTimeZoneInformation (TYPE_1__*) ; 
 int /*<<< orphan*/  lstrcmpW (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pGetDynamicTimeZoneInformation (TYPE_2__*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (scalar_t__*) ; 

__attribute__((used)) static void test_GetDynamicTimeZoneInformation(void)
{
    DYNAMIC_TIME_ZONE_INFORMATION dyninfo;
    TIME_ZONE_INFORMATION tzinfo;
    DWORD ret, ret2;

    if (!pGetDynamicTimeZoneInformation)
    {
        win_skip("GetDynamicTimeZoneInformation() is not supported.\n");
        return;
    }

    ret = pGetDynamicTimeZoneInformation(&dyninfo);
    ret2 = GetTimeZoneInformation(&tzinfo);
    ok(ret == ret2, "got %d, %d\n", ret, ret2);

    ok(dyninfo.Bias == tzinfo.Bias, "got %d, %d\n", dyninfo.Bias, tzinfo.Bias);
    ok(!lstrcmpW(dyninfo.StandardName, tzinfo.StandardName), "got std name %s, %s\n",
        wine_dbgstr_w(dyninfo.StandardName), wine_dbgstr_w(tzinfo.StandardName));
    ok(!memcmp(&dyninfo.StandardDate, &tzinfo.StandardDate, sizeof(dyninfo.StandardDate)), "got different StandardDate\n");
    ok(dyninfo.StandardBias == tzinfo.StandardBias, "got %d, %d\n", dyninfo.StandardBias, tzinfo.StandardBias);
    ok(!lstrcmpW(dyninfo.DaylightName, tzinfo.DaylightName), "got daylight name %s, %s\n",
        wine_dbgstr_w(dyninfo.DaylightName), wine_dbgstr_w(tzinfo.DaylightName));
    ok(!memcmp(&dyninfo.DaylightDate, &tzinfo.DaylightDate, sizeof(dyninfo.DaylightDate)), "got different DaylightDate\n");
    ok(dyninfo.TimeZoneKeyName[0] != 0, "got empty tz keyname\n");
    trace("Dyn TimeZoneKeyName %s\n", wine_dbgstr_w(dyninfo.TimeZoneKeyName));
}