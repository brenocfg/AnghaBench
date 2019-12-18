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
typedef  scalar_t__ uintmax_t ;
struct vlc_http_resource {struct vlc_http_msg* response; } ;
struct vlc_http_msg {int dummy; } ;
struct vlc_http_file {scalar_t__ offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_http_msg_destroy (struct vlc_http_msg*) ; 
 int vlc_http_msg_get_status (struct vlc_http_msg*) ; 
 struct vlc_http_msg* vlc_http_res_open (struct vlc_http_resource*,scalar_t__*) ; 

int vlc_http_file_seek(struct vlc_http_resource *res, uintmax_t offset)
{
    struct vlc_http_msg *resp = vlc_http_res_open(res, &offset);
    if (resp == NULL)
        return -1;

    struct vlc_http_file *file = (struct vlc_http_file *)res;

    int status = vlc_http_msg_get_status(resp);
    if (res->response != NULL)
    {   /* Accept the new and ditch the old one if:
         * - requested succeeded and range was accepted (206),
         * - requested failed due to out-of-range (416),
         * - request succeeded and seek offset is zero (2xx).
         */
        if (status != 206 && status != 416 && (offset != 0 || status >= 300))
        {
            vlc_http_msg_destroy(resp);
            return -1;
        }
        vlc_http_msg_destroy(res->response);
    }

    res->response = resp;
    file->offset = offset;
    return 0;
}