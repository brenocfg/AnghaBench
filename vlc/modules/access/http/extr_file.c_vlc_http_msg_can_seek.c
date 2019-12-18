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
 int vlc_http_msg_get_status (struct vlc_http_msg const*) ; 
 int /*<<< orphan*/ * vlc_http_msg_get_token (struct vlc_http_msg const*,char*,char*) ; 

__attribute__((used)) static bool vlc_http_msg_can_seek(const struct vlc_http_msg *resp)
{
    int status = vlc_http_msg_get_status(resp);
    if (status == 206 || status == 416)
        return true; /* Partial Content */

    return vlc_http_msg_get_token(resp, "Accept-Ranges", "bytes") != NULL;
}