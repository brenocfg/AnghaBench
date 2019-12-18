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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  SYSTEMTIME ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DATE_LONGDATE ; 
 int /*<<< orphan*/  GetDateFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  GetTimeFormat (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  LOCALE_USER_DEFAULT ; 
 int /*<<< orphan*/  UnixTimeToSystemTime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 

void xml_time_out(FILE* xmlout, time_t t)
{
    /* Windows specific */
    SYSTEMTIME st;
    char szLocalDate[255], szLocalTime[255];
    UnixTimeToSystemTime(t, &st);
    GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, szLocalDate, 255);
    GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, szLocalTime, 255);
    fprintf(xmlout, "%s %s", szLocalDate, szLocalTime);
}