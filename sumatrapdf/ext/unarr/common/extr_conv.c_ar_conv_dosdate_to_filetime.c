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
typedef  int uint32_t ;
typedef  int time_t ;
typedef  int time64_t ;
struct tm {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_isdst; } ;

/* Variables and functions */
 struct tm* gmtime (int*) ; 
 int mktime (struct tm*) ; 

time64_t ar_conv_dosdate_to_filetime(uint32_t dosdate)
{
    struct tm tm;
    time_t t1, t2;

    tm.tm_sec = (dosdate & 0x1F) * 2;
    tm.tm_min = (dosdate >> 5) & 0x3F;
    tm.tm_hour = (dosdate >> 11) & 0x1F;
    tm.tm_mday = (dosdate >> 16) & 0x1F;
    tm.tm_mon = ((dosdate >> 21) & 0x0F) - 1;
    tm.tm_year = ((dosdate >> 25) & 0x7F) + 80;
    tm.tm_isdst = -1;

    t1 = mktime(&tm);
    t2 = mktime(gmtime(&t1));

    return (time64_t)(2 * t1 - t2 + 11644473600) * 10000000;
}