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
struct tm {int tm_mday; int tm_min; int tm_mon; int tm_sec; int tm_wday; int tm_yday; int tm_year; scalar_t__ tm_hour; } ;

/* Variables and functions */
 char* asctime (struct tm*) ; 
 int /*<<< orphan*/  ok (int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void Test_asctime()
{
    /* Test asctime */
    struct tm time;
    char* timestr;
    char explowtime[] = "Mon Jun 04 00:30:20 1909\n"; /* XP's crt returns new line after the string */

    time.tm_hour = 0;
    time.tm_mday = 4;
    time.tm_min = 30;
    time.tm_mon = 5;
    time.tm_sec = 20;
    time.tm_wday = 1;
    time.tm_yday = 200;
    time.tm_year = 9;

    timestr = asctime(&time);
    ok(!strcmp(timestr, explowtime), "Wrong time returned, got %s\n", timestr);
}