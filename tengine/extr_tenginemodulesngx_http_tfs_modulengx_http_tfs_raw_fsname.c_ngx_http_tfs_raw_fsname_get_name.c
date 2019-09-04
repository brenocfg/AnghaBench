#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_4__ {scalar_t__ suffix; } ;
struct TYPE_5__ {char* file_name; scalar_t__ cluster_id; TYPE_1__ file; } ;
typedef  TYPE_2__ ngx_http_tfs_raw_fsname_t ;

/* Variables and functions */
 size_t NGX_HTTP_TFS_FILE_NAME_LEN ; 
 char NGX_HTTP_TFS_LARGE_FILE_KEY_CHAR ; 
 char NGX_HTTP_TFS_SMALL_FILE_KEY_CHAR ; 
 int /*<<< orphan*/  ngx_http_tfs_raw_fsname_encode (char*,char*) ; 

u_char*
ngx_http_tfs_raw_fsname_get_name(ngx_http_tfs_raw_fsname_t* fsname,
    unsigned large_flag, ngx_int_t simple_name)
{
    if (fsname != NULL) {
        if (simple_name) {
            /* zero suffix */
            fsname->file.suffix = 0;
        }

        ngx_http_tfs_raw_fsname_encode((u_char*) &(fsname->file),
                                       fsname->file_name + 2);

        if (large_flag) {
            fsname->file_name[0] = NGX_HTTP_TFS_LARGE_FILE_KEY_CHAR;

        } else {
            fsname->file_name[0] = NGX_HTTP_TFS_SMALL_FILE_KEY_CHAR;
        }
        fsname->file_name[1] = (u_char) ('0' + fsname->cluster_id);
        fsname->file_name[NGX_HTTP_TFS_FILE_NAME_LEN] = '\0';

        return fsname->file_name;
    }

    return NULL;
}