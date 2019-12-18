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
struct vlc_http_msg {scalar_t__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  vlc_http_is_agent (char const*) ; 
 int vlc_http_msg_add_header (struct vlc_http_msg*,char const*,char*,char const*) ; 

int vlc_http_msg_add_agent(struct vlc_http_msg *m, const char *str)
{
    const char *hname = (m->status < 0) ? "User-Agent" : "Server";

    if (!vlc_http_is_agent(str))
    {
        errno = EINVAL;
        return -1;
    }
    return vlc_http_msg_add_header(m, hname, "%s", str);
}