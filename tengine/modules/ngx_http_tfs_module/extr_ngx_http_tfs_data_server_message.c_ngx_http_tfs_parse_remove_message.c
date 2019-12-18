#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint16_t ;
struct TYPE_12__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_11__ {int size; } ;
struct TYPE_13__ {int /*<<< orphan*/  log; TYPE_3__ stat_info; TYPE_2__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_5__ ngx_http_tfs_t ;
struct TYPE_14__ {int code; int error_len; int /*<<< orphan*/  error_str; } ;
typedef  TYPE_6__ ngx_http_tfs_status_msg_t ;
struct TYPE_15__ {int type; } ;
typedef  TYPE_7__ ngx_http_tfs_header_t ;
typedef  int int32_t ;
struct TYPE_9__ {scalar_t__ pos; } ;
struct TYPE_10__ {TYPE_1__ body_buffer; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_HTTP_TFS_EXIT_GENERAL_ERROR ; 
#define  NGX_HTTP_TFS_STATUS_MESSAGE 128 
 int NGX_HTTP_TFS_STATUS_MESSAGE_OK ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int NGX_OK ; 
 int ngx_http_tfs_atoull (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_parse_remove_message(ngx_http_tfs_t *t)
{
    int32_t                     code, err_len;
    uint16_t                    type;
    uint64_t                    file_size;
    ngx_str_t                   err;
    ngx_int_t                   rc;
    ngx_http_tfs_header_t      *header;
    ngx_http_tfs_status_msg_t  *resp;

    header = (ngx_http_tfs_header_t *) t->header;
    type = header->type;

    switch (type) {
    case NGX_HTTP_TFS_STATUS_MESSAGE:
        resp = (ngx_http_tfs_status_msg_t *) t->tfs_peer->body_buffer.pos;
        err.len = 0;
        code = resp->code;

        if (code != NGX_HTTP_TFS_STATUS_MESSAGE_OK) {
            err_len = resp->error_len;
            if (err_len > 0) {
                err.data = resp->error_str;
                err.len = err_len;
            }

            ngx_log_error(NGX_LOG_ERR, t->log, 0,
                          "remove_file failed, error code (%d) err_msg(%V)",
                          code, &err);
            if (code <= NGX_HTTP_TFS_EXIT_GENERAL_ERROR) {
                return code;
            }

            return NGX_HTTP_TFS_EXIT_GENERAL_ERROR;
        }

        /* on success, return is remove file's size */
        err_len = resp->error_len;
        file_size = 0;
        if (err_len > 1) {
            rc = ngx_http_tfs_atoull(resp->error_str,
                                     err_len - 1,
                                     (unsigned long long *) &file_size);
            if (rc == NGX_ERROR) {
                return NGX_ERROR;
            }
            t->stat_info.size += file_size;
        }

        ngx_log_error(NGX_LOG_INFO, t->log, 0,
                      "remove_file success, file_size: %uL ",
                      file_size);

        return NGX_OK;
    default:
        ngx_log_error(NGX_LOG_INFO, t->log, 0,
                      "remove file(ds) response msg type is invalid %d ", type);
    }

    return NGX_ERROR;
}