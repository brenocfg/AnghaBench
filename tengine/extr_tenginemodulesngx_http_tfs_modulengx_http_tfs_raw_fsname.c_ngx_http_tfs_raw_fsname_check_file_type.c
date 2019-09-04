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
struct TYPE_3__ {scalar_t__* data; scalar_t__ len; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_raw_file_type_e ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_TFS_FILE_NAME_LEN ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_INVALID_FILE_TYPE ; 
 scalar_t__ NGX_HTTP_TFS_LARGE_FILE_KEY_CHAR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_LARGE_FILE_TYPE ; 
 scalar_t__ NGX_HTTP_TFS_SMALL_FILE_KEY_CHAR ; 
 int /*<<< orphan*/  NGX_HTTP_TFS_SMALL_FILE_TYPE ; 

ngx_http_tfs_raw_file_type_e
ngx_http_tfs_raw_fsname_check_file_type(ngx_str_t *tfs_name)
{
    ngx_http_tfs_raw_file_type_e file_type = NGX_HTTP_TFS_INVALID_FILE_TYPE;

    if (tfs_name->data != NULL
        && tfs_name->len >= NGX_HTTP_TFS_FILE_NAME_LEN)
    {
        if (tfs_name->data[0] == NGX_HTTP_TFS_LARGE_FILE_KEY_CHAR) {
            file_type = NGX_HTTP_TFS_LARGE_FILE_TYPE;

        } else if (tfs_name->data[0] == NGX_HTTP_TFS_SMALL_FILE_KEY_CHAR) {
            file_type = NGX_HTTP_TFS_SMALL_FILE_TYPE;
        }
    }

    return file_type;
}