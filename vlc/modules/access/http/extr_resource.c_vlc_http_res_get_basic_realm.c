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
struct vlc_http_resource {int /*<<< orphan*/  response; } ;

/* Variables and functions */
 char* vlc_http_msg_get_basic_realm (int /*<<< orphan*/ ) ; 
 int vlc_http_res_get_status (struct vlc_http_resource*) ; 

char *vlc_http_res_get_basic_realm(struct vlc_http_resource *res)
{
    int status = vlc_http_res_get_status(res);
    if (status != 401)
        return NULL;
    return vlc_http_msg_get_basic_realm(res->response);
}