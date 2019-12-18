#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vlc_http_resource {int /*<<< orphan*/ * response; } ;
struct vlc_http_file {scalar_t__ offset; } ;
struct TYPE_5__ {scalar_t__ i_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 TYPE_1__* vlc_http_error ; 
 scalar_t__ vlc_http_file_seek (struct vlc_http_resource*,scalar_t__) ; 
 scalar_t__ vlc_http_msg_can_seek (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_http_msg_get_file_size (int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_http_res_read (struct vlc_http_resource*) ; 

block_t *vlc_http_file_read(struct vlc_http_resource *res)
{
    struct vlc_http_file *file = (struct vlc_http_file *)res;
    block_t *block = vlc_http_res_read(res);

    if (block == vlc_http_error)
    {   /* Automatically reconnect on error if server supports seek */
        if (res->response != NULL
         && vlc_http_msg_can_seek(res->response)
         && file->offset < vlc_http_msg_get_file_size(res->response)
         && vlc_http_file_seek(res, file->offset) == 0)
            block = vlc_http_res_read(res);

        if (block == vlc_http_error)
            return NULL;
    }

    if (block == NULL)
        return NULL; /* End of stream */

    file->offset += block->i_buffer;
    return block;
}