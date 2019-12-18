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
struct vlc_http_msg {int dummy; } ;
struct tm {size_t tm_wday; size_t tm_mon; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_hour; scalar_t__ tm_year; int /*<<< orphan*/  tm_mday; } ;

/* Variables and functions */
 int /*<<< orphan*/ * gmtime_r (int /*<<< orphan*/  const*,struct tm*) ; 
 int /*<<< orphan*/ * vlc_http_days ; 
 int /*<<< orphan*/ * vlc_http_months ; 
 int vlc_http_msg_add_header (struct vlc_http_msg*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vlc_http_msg_add_time(struct vlc_http_msg *m, const char *hname,
                          const time_t *t)
{
    struct tm tm;

    if (gmtime_r(t, &tm) == NULL)
        return -1;
    return vlc_http_msg_add_header(m, hname,
                                   "%s, %02d %s %04d %02d:%02d:%02d GMT",
                                   vlc_http_days[tm.tm_wday], tm.tm_mday,
                                   vlc_http_months[tm.tm_mon],
                                   1900 + tm.tm_year,
                                   tm.tm_hour, tm.tm_min, tm.tm_sec);
}