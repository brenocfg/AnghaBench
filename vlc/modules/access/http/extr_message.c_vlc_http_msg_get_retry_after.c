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
typedef  scalar_t__ time_t ;
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 unsigned long strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 scalar_t__ vlc_http_mktime (char const*) ; 
 char* vlc_http_msg_get_header (struct vlc_http_msg const*,char*) ; 

unsigned vlc_http_msg_get_retry_after(const struct vlc_http_msg *m)
{
    const char *str = vlc_http_msg_get_header(m, "Retry-After");
    if (str == NULL)
        return 0;

    char *end;
    unsigned long delay = strtoul(str, &end, 10);
    if (end != str && *end == '\0')
        return delay;

    time_t t = vlc_http_mktime(str);
    if (t != (time_t)-1)
    {
        time_t now;

        time(&now);
        if (t >= now)
            return t - now;
    }
    return 0;
}