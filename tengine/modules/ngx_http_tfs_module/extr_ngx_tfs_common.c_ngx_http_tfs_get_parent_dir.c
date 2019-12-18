#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_uint_t ;
struct TYPE_3__ {int len; char* data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int ngx_int_t ;

/* Variables and functions */

ngx_int_t
ngx_http_tfs_get_parent_dir(ngx_str_t *file_path, ngx_int_t *dir_level)
{
    ngx_uint_t  i, last_slash_pos;

    last_slash_pos = 0;

    if (dir_level != NULL) {
        *dir_level = 0;
    }

    for (i = 0; i < (file_path->len - 1); i++) {
        if (file_path->data[i] == '/'
            && (file_path->data[i + 1]) != '/')
        {
            last_slash_pos = i;
            if (dir_level != NULL) {
                (*dir_level)++;
            }
        }
    }

    return last_slash_pos + 1;
}