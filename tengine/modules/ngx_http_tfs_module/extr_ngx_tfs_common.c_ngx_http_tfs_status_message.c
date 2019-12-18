#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_8__ {scalar_t__ code; scalar_t__ error_len; int /*<<< orphan*/  error_str; } ;
typedef  TYPE_2__ ngx_http_tfs_status_msg_t ;
struct TYPE_9__ {scalar_t__ pos; } ;
typedef  TYPE_3__ ngx_buf_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ NGX_HTTP_TFS_EXIT_GENERAL_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_STATUS_MESSAGE_OK ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*,...) ; 

ngx_int_t
ngx_http_tfs_status_message(ngx_buf_t *b, ngx_str_t *action, ngx_log_t *log)
{
    int32_t                     code, err_len;
    ngx_str_t                   err;
    ngx_http_tfs_status_msg_t  *res;

    res = (ngx_http_tfs_status_msg_t *) b->pos;
    err.len = 0;
    code = res->code;

    if (code != NGX_HTTP_TFS_STATUS_MESSAGE_OK) {
        err_len = res->error_len;
        if (err_len > 0) {
            err.data = res->error_str;
            err.len = err_len;
        }

        ngx_log_error(NGX_LOG_ERR, log, 0,
                      "%V failed error code (%d) err_msg(%V)",
                      action, code, &err);
        if (code <= NGX_HTTP_TFS_EXIT_GENERAL_ERROR) {
            return code;
        }

        return NGX_HTTP_TFS_EXIT_GENERAL_ERROR;
    }

    ngx_log_error(NGX_LOG_INFO, log, 0, "%V success ", action);
    return NGX_OK;
}