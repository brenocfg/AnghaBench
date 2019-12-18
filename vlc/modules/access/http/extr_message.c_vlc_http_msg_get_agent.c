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
 scalar_t__ vlc_http_is_agent (char const*) ; 
 char* vlc_http_msg_get_header (struct vlc_http_msg const*,char const*) ; 

const char *vlc_http_msg_get_agent(const struct vlc_http_msg *m)
{
    const char *hname = (m->status < 0) ? "User-Agent" : "Server";
    const char *str = vlc_http_msg_get_header(m, hname);

    return (str != NULL && vlc_http_is_agent(str)) ? str : NULL;
}