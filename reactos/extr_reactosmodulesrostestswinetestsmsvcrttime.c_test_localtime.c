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
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_mon; int tm_yday; int tm_mday; scalar_t__ tm_hour; scalar_t__ tm_min; scalar_t__ tm_sec; scalar_t__ tm_isdst; int /*<<< orphan*/  tm_wday; } ;
struct TYPE_3__ {int Bias; int DaylightBias; int StandardBias; } ;
typedef  TYPE_1__ TIME_ZONE_INFORMATION ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ GetTimeZoneInformation (TYPE_1__*) ; 
 int SECSPERDAY ; 
 int SECSPERMIN ; 
 scalar_t__ TIME_ZONE_ID_INVALID ; 
 int /*<<< orphan*/  _snprintf (char*,int,char*,char*) ; 
 int get_test_year (scalar_t__*) ; 
 char* getenv (char*) ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  putenv (char*) ; 

__attribute__((used)) static void test_localtime(void)
{
    TIME_ZONE_INFORMATION tzinfo;
    DWORD res =  GetTimeZoneInformation(&tzinfo);
    time_t gmt, ref;

    char TZ_env[256];
    struct tm* lt;
    int year = get_test_year( &ref );
    int is_leap = !(year % 4) && ((year % 100) || !((year + 300) % 400));

    gmt = ref + SECSPERDAY + tzinfo.Bias * SECSPERMIN;
    ok (res != TIME_ZONE_ID_INVALID, "GetTimeZoneInformation failed\n");
    lt = localtime(&gmt);
    gmt += (lt->tm_isdst ? tzinfo.DaylightBias : tzinfo.StandardBias) * SECSPERMIN;
    lt = localtime(&gmt);
    ok(((lt->tm_year == year) && (lt->tm_mon  == 0) && (lt->tm_yday  == 1) &&
	(lt->tm_mday ==  2) && (lt->tm_hour  == 0) &&
	(lt->tm_min  ==  0) && (lt->tm_sec  == 0)),
       "Wrong date:Year %d mon %d yday %d mday %d wday %d hour %d min %d sec %d dst %d\n",
       lt->tm_year, lt->tm_mon, lt->tm_yday, lt->tm_mday, lt->tm_wday, lt->tm_hour, 
       lt->tm_min, lt->tm_sec, lt->tm_isdst); 

    _snprintf(TZ_env,255,"TZ=%s",(getenv("TZ")?getenv("TZ"):""));
    putenv("TZ=GMT");
    lt = localtime(&gmt);
    ok(((lt->tm_year == year) && (lt->tm_mon  == 0) && (lt->tm_yday  == 1) &&
	(lt->tm_mday ==  2) && (lt->tm_hour  == 0) &&
	(lt->tm_min  ==  0) && (lt->tm_sec  == 0)),
       "Wrong date:Year %d mon %d yday %d mday %d wday %d hour %d min %d sec %d dst %d\n",
       lt->tm_year, lt->tm_mon, lt->tm_yday, lt->tm_mday, lt->tm_wday, lt->tm_hour, 
       lt->tm_min, lt->tm_sec, lt->tm_isdst); 
    putenv(TZ_env);

    /* June 22 */
    gmt = ref + 202 * SECSPERDAY + tzinfo.Bias * SECSPERMIN;
    lt = localtime(&gmt);
    gmt += (lt->tm_isdst ? tzinfo.DaylightBias : tzinfo.StandardBias) * SECSPERMIN;
    lt = localtime(&gmt);
    ok(((lt->tm_year == year) && (lt->tm_mon  == 6) && (lt->tm_yday  == 202) &&
	(lt->tm_mday == 22 - is_leap) && (lt->tm_hour  == 0) &&
	(lt->tm_min  ==  0) && (lt->tm_sec  == 0)),
       "Wrong date:Year %d mon %d yday %d mday %d wday %d hour %d min %d sec %d dst %d\n",
       lt->tm_year, lt->tm_mon, lt->tm_yday, lt->tm_mday, lt->tm_wday, lt->tm_hour, 
       lt->tm_min, lt->tm_sec, lt->tm_isdst); 
}