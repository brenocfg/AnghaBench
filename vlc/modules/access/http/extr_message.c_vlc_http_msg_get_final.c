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
struct vlc_http_msg {int dummy; } ;

/* Variables and functions */
 int vlc_http_msg_get_status (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_msg_iterate (struct vlc_http_msg*) ; 

struct vlc_http_msg *vlc_http_msg_get_final(struct vlc_http_msg *m)
{
    while (m != NULL && (vlc_http_msg_get_status(m) / 100) == 1)
        m = vlc_http_msg_iterate(m);
    return m;
}