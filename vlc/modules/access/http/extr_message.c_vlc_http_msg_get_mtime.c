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

/* Variables and functions */
 int /*<<< orphan*/  vlc_http_msg_get_time (struct vlc_http_msg const*,char*) ; 

time_t vlc_http_msg_get_mtime(const struct vlc_http_msg *m)
{
    return vlc_http_msg_get_time(m, "Last-Modified");
}