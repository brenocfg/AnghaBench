#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tzinfo ;
typedef  int /*<<< orphan*/  tziNew ;
struct TYPE_15__ {int Month; int Day; int Weekday; int Year; } ;
struct TYPE_14__ {int Month; int Day; int Weekday; int Year; } ;
struct TYPE_17__ {int Bias; int DaylightBias; int StandardBias; TYPE_4__ StandardDate; TYPE_3__ DaylightDate; } ;
struct TYPE_13__ {int wMonth; int wDayOfWeek; int wDay; int wHour; } ;
struct TYPE_12__ {int wMonth; int wDayOfWeek; int wDay; int wHour; } ;
struct TYPE_16__ {int Bias; int StandardBias; int DaylightBias; int /*<<< orphan*/  DaylightName; int /*<<< orphan*/  StandardName; TYPE_2__ DaylightDate; TYPE_1__ StandardDate; } ;
typedef  TYPE_5__ TIME_ZONE_INFORMATION ;
typedef  TYPE_6__ RTL_TIME_ZONE_INFORMATION ;
typedef  int NTSTATUS ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int GetLastError () ; 
 scalar_t__ GetTimeZoneInformation (TYPE_5__*) ; 
 int STATUS_SUCCESS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int SetTimeZoneInformation (TYPE_5__*) ; 
 scalar_t__ TIME_ZONE_ID_DAYLIGHT ; 
 scalar_t__ TIME_ZONE_ID_STANDARD ; 
 scalar_t__ TIME_ZONE_ID_UNKNOWN ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int pRtlQueryTimeZoneInformation (TYPE_6__*) ; 
 int /*<<< orphan*/  wcscmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_RtlQueryTimeZoneInformation(void)
{
    RTL_TIME_ZONE_INFORMATION tzinfo;
    NTSTATUS status;
    TIME_ZONE_INFORMATION tziOld, tziNew, tziTest;
    DWORD dwRet;

    // Retrieve the current time zone information

    dwRet = GetTimeZoneInformation(&tziOld);

    ok(dwRet == TIME_ZONE_ID_STANDARD || dwRet == TIME_ZONE_ID_UNKNOWN || dwRet == TIME_ZONE_ID_DAYLIGHT,
        "Get Time Zone Name failed with error = %ld.\n", GetLastError()); 

    // Adjust the time zone information

    ZeroMemory(&tziNew, sizeof(tziNew));
    tziNew.Bias = 360;
    wcscpy(tziNew.StandardName, L"Test Standard Zone");
    tziNew.StandardDate.wMonth = 11;
    tziNew.StandardDate.wDayOfWeek = 5;
    tziNew.StandardDate.wDay = 3;
    tziNew.StandardDate.wHour = 2;
    tziNew.StandardBias = 120;

    wcscpy(tziNew.DaylightName, L"Test Daylight Zone");
    tziNew.DaylightDate.wMonth = 4;
    tziNew.DaylightDate.wDayOfWeek = 6;
    tziNew.DaylightDate.wDay = 2;
    tziNew.DaylightDate.wHour = 2;
    tziNew.DaylightBias = -60;

    // Set up SetLastError with known value for later testing

    SetLastError(0xDEADBEEF);

    ok(SetTimeZoneInformation(&tziNew) , 
        "Set Time Zone Information failed with error = %ld.\n", GetLastError());

    // if we got an error the function failed, so there is not much else we can do

    if(GetLastError() != 0xDEADBEEF)
    {
        win_skip("SetTimeZoneInformation() is not available, so tests cannot be run.\n");
        return;
    }

    // Retrieve and display the newly set time zone information

    dwRet = GetTimeZoneInformation(&tziTest);

    ok(dwRet == TIME_ZONE_ID_STANDARD || dwRet == TIME_ZONE_ID_UNKNOWN || dwRet == TIME_ZONE_ID_DAYLIGHT,
        "Get Time Zone Information Returned failed with error = %ld.\n", GetLastError()); 

    ok(!wcscmp(tziTest.StandardName, tziNew.StandardName),
        "Standard Time Zone Name = %ls, expected %ls.\n", tziTest.StandardName, tziNew.StandardName);

    ok(!wcscmp(tziTest.DaylightName, tziNew.DaylightName),
        "Standard Time Zone Name = %ls, expected %ls.\n", tziTest.DaylightName, tziNew.DaylightName);

    /* test RtlQueryTimeZoneInformation returns a TIME_ZONE_INFORMATION structure */

    if (!pRtlQueryTimeZoneInformation)
    {
        win_skip("pRtlQueryTimeZoneInformation() fails, so tests cannot be run.\n");
        return;
    }

    /* Clear Time Zone Info field */
    memset(&tzinfo, 0, sizeof(tzinfo));

    /* Read Time Zone Info */
    status = pRtlQueryTimeZoneInformation(&tzinfo);
    ok(status == STATUS_SUCCESS, "pRtlQueryTimeZoneInformation failed, got %08lx\n", status);

    /* Check for the Daylight Date Info */
    ok(tzinfo.DaylightDate.Month == 4, "tzinfo.DaylightDate.wMonth expected '4', got '%d'.\n", tzinfo.DaylightDate.Month);
    ok(tzinfo.DaylightDate.Day == 2, "tzinfo.DaylightDate.wDay expected '2', got '%d'.\n", tzinfo.DaylightDate.Day);
    ok(tzinfo.DaylightDate.Weekday == 6, "tzinfo.DaylightDate.wDayOfWeek expected '6', got '%d'.\n", tzinfo.DaylightDate.Weekday);
    ok(tzinfo.DaylightDate.Year == 0, "tzinfo.DaylightDate.wYear expected '0', got '%d'.\n", tzinfo.DaylightDate.Year);

    /* Check for the Standard Data Info */
    ok(tzinfo.StandardDate.Month == 11, "tzinfo.StandardDate.wMonth expected '11', got '%d'.\n", tzinfo.StandardDate.Month);
    ok(tzinfo.StandardDate.Day == 3, "tzinfo.StandardDate.wDay expected '3', got '%d'.\n", tzinfo.StandardDate.Day);
    ok(tzinfo.StandardDate.Weekday == 5, "tzinfo.StandardDate.wDayOfWeek expected '5', got '%d'.\n", tzinfo.StandardDate.Weekday);
    ok(tzinfo.StandardDate.Year == 0, "tzinfo.StandardDate.wYear expected '0', got '%d'.\n", tzinfo.StandardDate.Year);

    /* Check for the Bias Info */
    ok(tzinfo.Bias == 360, "tzinfo.Bias expected '360', got '%ld'.\n", tzinfo.Bias);
    ok(tzinfo.DaylightBias == -60, "tzinfo.DaylightBias expected '-60', got '%ld'.\n", tzinfo.DaylightBias);
    ok(tzinfo.StandardBias == 120, "tzinfo.StandardBias expected '120', got '%ld'.\n", tzinfo.StandardBias);

    // Restore the original time zone information and put things back like we found them originally
    ok(SetTimeZoneInformation(&tziOld),
        "Set Time Zone Information failed with error = %ld.\n", GetLastError());

}