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
typedef  int time_t ;
struct tm {char tm_mday; int tm_year; int tm_hour; int tm_min; int tm_sec; int tm_mon; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int sscanf (char const*,char*,char*,char*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int timegm (struct tm*) ; 
 int /*<<< orphan*/ * vlc_http_months ; 

__attribute__((used)) static time_t vlc_http_mktime(const char *str)
{   /* IETF RFC7231 §7.1.1.1 */
    struct tm tm;
    char mon[4];

    /* Internet Message Format date */
    if (sscanf(str, "%*c%*c%*c, %2d %3s %4d %2d:%2d:%2d", &tm.tm_mday, mon,
               &tm.tm_year, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) == 6
    /* ANSI C format */
     || sscanf(str, "%*3s %3s %2d %2d:%2d:%2d %4d", mon, &tm.tm_mday,
               &tm.tm_hour, &tm.tm_min, &tm.tm_sec, &tm.tm_year) == 6)
        tm.tm_year -= 1900;
    /* RFC850 date */
    else if (sscanf(str, "%*[^,], %2d-%3s-%2d %2d:%2d:%2d", &tm.tm_mday, mon,
                    &tm.tm_year, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) == 6)
    {
        if (tm.tm_year <= 75)
            tm.tm_year += 100; /* Y2K compat, sort of */
    }
    else /* Unknown format */
        goto error;

    for (tm.tm_mon = 0; tm.tm_mon < 12; tm.tm_mon++)
        if (!strcmp(mon, vlc_http_months[tm.tm_mon])) /* found month */
            return timegm(&tm);
error:
    errno = EINVAL;
    return -1; /* invalid month */
}