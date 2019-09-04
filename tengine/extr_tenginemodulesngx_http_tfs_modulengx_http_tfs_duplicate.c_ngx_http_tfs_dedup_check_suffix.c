#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ len; scalar_t__ data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_FILE_NAME_LEN ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_strncmp (scalar_t__,scalar_t__,scalar_t__) ; 

ngx_int_t
ngx_http_tfs_dedup_check_suffix(ngx_str_t *tfs_name, ngx_str_t *suffix)
{
    ngx_int_t  rc;

    rc = NGX_ERROR;
    if ((tfs_name->len == NGX_HTTP_TFS_FILE_NAME_LEN && suffix->len == 0)
        || (tfs_name->len > NGX_HTTP_TFS_FILE_NAME_LEN && suffix->len > 0
            && ((tfs_name->len - NGX_HTTP_TFS_FILE_NAME_LEN) == suffix->len)
            && (ngx_strncmp(suffix->data,
                            tfs_name->data + NGX_HTTP_TFS_FILE_NAME_LEN,
                            suffix->len) == 0)))
    {
        rc = NGX_OK;
    }

    return rc;
}