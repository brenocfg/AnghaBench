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
 char* strdup (char const*) ; 
 char* vlc_http_msg_get_header (int /*<<< orphan*/ ,char*) ; 
 int vlc_http_res_get_status (struct vlc_http_resource*) ; 

char *vlc_http_res_get_type(struct vlc_http_resource *res)
{
    int status = vlc_http_res_get_status(res);
    if (status < 200 || status >= 300)
        return NULL;

    const char *type = vlc_http_msg_get_header(res->response, "Content-Type");
    return (type != NULL) ? strdup(type) : NULL;
}