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
typedef  int uintmax_t ;
struct vlc_http_resource {int /*<<< orphan*/  response; } ;

/* Variables and functions */
 int vlc_http_msg_get_file_size (int /*<<< orphan*/ ) ; 
 int vlc_http_msg_get_size (int /*<<< orphan*/ ) ; 
 int vlc_http_res_get_status (struct vlc_http_resource*) ; 

uintmax_t vlc_http_file_get_size(struct vlc_http_resource *res)
{
    int status = vlc_http_res_get_status(res);
    if (status < 0)
        return -1;

    uintmax_t ret = vlc_http_msg_get_file_size(res->response);
    if (ret != (uintmax_t)-1)
        return ret;

    if (status >= 300 || status == 201)
        return -1; /* Error or redirection, size is unknown/irrelevant. */

    /* Content-Range is meaningless here (see RFC7233 B), so check if the size
     * of the response entity body is known. */
    return vlc_http_msg_get_size(res->response);
}