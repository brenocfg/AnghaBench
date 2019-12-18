#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dyn_tzinfo ;
typedef  int WORD ;
typedef  char WCHAR ;
struct TYPE_16__ {int wMonth; } ;
struct TYPE_15__ {int /*<<< orphan*/  TimeZoneKeyName; scalar_t__ DynamicDaylightTimeDisabled; } ;
struct TYPE_14__ {int wYear; } ;
struct TYPE_13__ {int Bias; int StandardBias; int DaylightBias; int /*<<< orphan*/  DaylightName; int /*<<< orphan*/  StandardName; TYPE_8__ DaylightDate; TYPE_8__ StandardDate; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  TYPE_2__ SYSTEMTIME ;
typedef  TYPE_3__ DYNAMIC_TIME_ZONE_INFORMATION ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int ERROR_FILE_NOT_FOUND ; 
 scalar_t__ FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetLocalTime (TYPE_2__*) ; 
 int /*<<< orphan*/  GetTimeZoneInformation (TYPE_1__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ broken (int) ; 
 int day_of_month (TYPE_8__*,int) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  memcmp (TYPE_8__*,TYPE_8__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pGetDynamicTimeZoneInformation (TYPE_3__*) ; 
 scalar_t__ pGetTimeZoneInformationForYear (int,TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_GetTimeZoneInformationForYear(void)
{
    BOOL ret;
    SYSTEMTIME systemtime;
    TIME_ZONE_INFORMATION local_tzinfo, tzinfo, tzinfo2;
    DYNAMIC_TIME_ZONE_INFORMATION dyn_tzinfo;
    static const WCHAR std_tzname[] = {'G','r','e','e','n','l','a','n','d',' ','S','t','a','n','d','a','r','d',' ','T','i','m','e',0};
    static const WCHAR dlt_tzname[] = {'G','r','e','e','n','l','a','n','d',' ','D','a','y','l','i','g','h','t',' ','T','i','m','e',0};
    WORD std_day, dlt_day;

    if (!pGetTimeZoneInformationForYear || !pGetDynamicTimeZoneInformation)
    {
        win_skip("GetTimeZoneInformationForYear not available\n");
        return;
    }

    GetLocalTime(&systemtime);

    GetTimeZoneInformation(&local_tzinfo);

    ret = pGetTimeZoneInformationForYear(systemtime.wYear, NULL, &tzinfo);
    ok(ret == TRUE, "GetTimeZoneInformationForYear failed, err %u\n", GetLastError());
    ok(tzinfo.Bias == local_tzinfo.Bias, "Expected Bias %d, got %d\n", local_tzinfo.Bias, tzinfo.Bias);
    ok(!lstrcmpW(tzinfo.StandardName, local_tzinfo.StandardName),
        "Expected StandardName %s, got %s\n", wine_dbgstr_w(local_tzinfo.StandardName), wine_dbgstr_w(tzinfo.StandardName));
    ok(!memcmp(&tzinfo.StandardDate, &local_tzinfo.StandardDate, sizeof(SYSTEMTIME)), "StandardDate does not match\n");
    ok(tzinfo.StandardBias == local_tzinfo.StandardBias, "Expected StandardBias %d, got %d\n", local_tzinfo.StandardBias, tzinfo.StandardBias);
    ok(!lstrcmpW(tzinfo.DaylightName, local_tzinfo.DaylightName),
        "Expected DaylightName %s, got %s\n", wine_dbgstr_w(local_tzinfo.DaylightName), wine_dbgstr_w(tzinfo.DaylightName));
    ok(!memcmp(&tzinfo.DaylightDate, &local_tzinfo.DaylightDate, sizeof(SYSTEMTIME)), "DaylightDate does not match\n");
    ok(tzinfo.DaylightBias == local_tzinfo.DaylightBias, "Expected DaylightBias %d, got %d\n", local_tzinfo.DaylightBias, tzinfo.DaylightBias);

    pGetDynamicTimeZoneInformation(&dyn_tzinfo);

    ret = pGetTimeZoneInformationForYear(systemtime.wYear, &dyn_tzinfo, &tzinfo);
    ok(ret == TRUE, "GetTimeZoneInformationForYear failed, err %u\n", GetLastError());
    ok(tzinfo.Bias == local_tzinfo.Bias, "Expected Bias %d, got %d\n", local_tzinfo.Bias, tzinfo.Bias);
    ok(!lstrcmpW(tzinfo.StandardName, local_tzinfo.StandardName),
        "Expected StandardName %s, got %s\n", wine_dbgstr_w(local_tzinfo.StandardName), wine_dbgstr_w(tzinfo.StandardName));
    ok(!memcmp(&tzinfo.StandardDate, &local_tzinfo.StandardDate, sizeof(SYSTEMTIME)), "StandardDate does not match\n");
    ok(tzinfo.StandardBias == local_tzinfo.StandardBias, "Expected StandardBias %d, got %d\n", local_tzinfo.StandardBias, tzinfo.StandardBias);
    ok(!lstrcmpW(tzinfo.DaylightName, local_tzinfo.DaylightName),
        "Expected DaylightName %s, got %s\n", wine_dbgstr_w(local_tzinfo.DaylightName), wine_dbgstr_w(tzinfo.DaylightName));
    ok(!memcmp(&tzinfo.DaylightDate, &local_tzinfo.DaylightDate, sizeof(SYSTEMTIME)), "DaylightDate does not match\n");
    ok(tzinfo.DaylightBias == local_tzinfo.DaylightBias, "Expected DaylightBias %d, got %d\n", local_tzinfo.DaylightBias, tzinfo.DaylightBias);

    memset(&dyn_tzinfo, 0xaa, sizeof(dyn_tzinfo));
    lstrcpyW(dyn_tzinfo.TimeZoneKeyName, std_tzname);
    dyn_tzinfo.DynamicDaylightTimeDisabled = FALSE;

    ret = pGetTimeZoneInformationForYear(2015, &dyn_tzinfo, &tzinfo);
    ok(ret == TRUE, "GetTimeZoneInformationForYear failed, err %u\n", GetLastError());
    ok(tzinfo.Bias == 180, "Expected Bias 180, got %d\n", tzinfo.Bias);
    ok(tzinfo.StandardDate.wMonth == 10, "Expected standard month 10, got %d\n", tzinfo.StandardDate.wMonth);
    std_day = day_of_month(&tzinfo.StandardDate, 2015);
    ok(std_day == 24, "Expected standard day 24, got %d\n", std_day);
    ok(tzinfo.StandardBias == 0, "Expected StandardBias 0, got %d\n", tzinfo.StandardBias);
    ok(tzinfo.DaylightDate.wMonth == 3, "Expected daylight month 3, got %d\n", tzinfo.DaylightDate.wMonth);
    dlt_day = day_of_month(&tzinfo.DaylightDate, 2015);
    ok(dlt_day == 28, "Expected daylight day 28, got %d\n", dlt_day);
    ok(tzinfo.DaylightBias == -60, "Expected DaylightBias -60, got %d\n", tzinfo.DaylightBias);

    ret = pGetTimeZoneInformationForYear(2016, &dyn_tzinfo, &tzinfo2);
    ok(ret == TRUE, "GetTimeZoneInformationForYear failed, err %u\n", GetLastError());
    ok(!lstrcmpW(tzinfo.StandardName, tzinfo2.StandardName),
        "Got differing StandardName values %s and %s\n",
        wine_dbgstr_w(tzinfo.StandardName), wine_dbgstr_w(tzinfo2.StandardName));
    ok(!lstrcmpW(tzinfo.DaylightName, tzinfo2.DaylightName),
        "Got differing DaylightName values %s and %s\n",
        wine_dbgstr_w(tzinfo.DaylightName), wine_dbgstr_w(tzinfo2.DaylightName));

    memset(&dyn_tzinfo, 0xaa, sizeof(dyn_tzinfo));
    lstrcpyW(dyn_tzinfo.TimeZoneKeyName, dlt_tzname);

    SetLastError(0xdeadbeef);
    ret = pGetTimeZoneInformationForYear(2015, &dyn_tzinfo, &tzinfo);
    ok((ret == FALSE && GetLastError() == ERROR_FILE_NOT_FOUND) ||
       broken(ret == TRUE) /* vista,7 */,
       "GetTimeZoneInformationForYear err %u\n", GetLastError());
}