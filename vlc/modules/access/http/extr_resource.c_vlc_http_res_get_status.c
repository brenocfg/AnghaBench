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
struct vlc_http_resource {int failure; int /*<<< orphan*/ * response; } ;

/* Variables and functions */
 int vlc_http_msg_get_status (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_http_res_open (struct vlc_http_resource*,struct vlc_http_resource*) ; 

int vlc_http_res_get_status(struct vlc_http_resource *res)
{
    if (res->response == NULL)
    {
        if (res->failure)
            return -1;

        res->response = vlc_http_res_open(res, res + 1);
        if (res->response == NULL)
        {
            res->failure = true;
            return -1;
        }
    }
    return vlc_http_msg_get_status(res->response);
}