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
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int vlc_http_msg_add_time (struct vlc_http_msg*,char*,int /*<<< orphan*/ *) ; 

int vlc_http_msg_add_atime(struct vlc_http_msg *m)
{
    time_t now;

    time(&now);
    return vlc_http_msg_add_time(m, "Date", &now);
}