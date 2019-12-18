#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
typedef  int ngx_int_t ;
struct TYPE_8__ {int cluster_id; } ;
struct TYPE_9__ {int group_count; int group_seq; int /*<<< orphan*/  log; TYPE_2__ file; TYPE_5__* tfs_peer; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_10__ {scalar_t__ code; scalar_t__ error_len; int /*<<< orphan*/  error_str; } ;
typedef  TYPE_4__ ngx_http_tfs_status_msg_t ;
struct TYPE_7__ {scalar_t__ pos; } ;
struct TYPE_11__ {TYPE_1__ body_buffer; } ;
typedef  TYPE_5__ ngx_http_tfs_peer_connection_t ;

/* Variables and functions */
 int NGX_ERROR ; 
#define  NGX_HTTP_TFS_CMD_GET_CLUSTER_ID_NS 130 
#define  NGX_HTTP_TFS_CMD_GET_GROUP_COUNT 129 
#define  NGX_HTTP_TFS_CMD_GET_GROUP_SEQ 128 
 scalar_t__ NGX_HTTP_TFS_STATUS_MESSAGE_OK ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int NGX_OK ; 
 void* ngx_atoi (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_parse_ctl_message(ngx_http_tfs_t *t, uint8_t cmd)
{
    uint32_t                         code;
    ngx_int_t                        cluster_id;
    ngx_http_tfs_status_msg_t       *res;
    ngx_http_tfs_peer_connection_t  *tp;

    tp = t->tfs_peer;
    res = (ngx_http_tfs_status_msg_t *) tp->body_buffer.pos;
    code = res->code;

    if (code == NGX_HTTP_TFS_STATUS_MESSAGE_OK && res->error_len > 0) {
        switch(cmd) {
        case NGX_HTTP_TFS_CMD_GET_CLUSTER_ID_NS:
            cluster_id = ngx_atoi(res->error_str, res->error_len - 1);
            cluster_id = cluster_id - '0';

            if (cluster_id == NGX_ERROR) {
                ngx_log_error(NGX_LOG_ERR, t->log, 0,
                              "invalid cluster id \"%s\" ", res->error_str);
                return NGX_ERROR;
            }

            t->file.cluster_id = cluster_id;
            break;
        case NGX_HTTP_TFS_CMD_GET_GROUP_COUNT:
            t->group_count = ngx_atoi(res->error_str, res->error_len - 1);
            if (t->group_count == NGX_ERROR || t->group_count <= 0) {
                ngx_log_error(NGX_LOG_WARN, t->log, 0,
                              "invalid  group count \"%s\" ", res->error_str);
                t->group_count = 1; /* compatible with old ns(1.3) */
            }
            break;
        case NGX_HTTP_TFS_CMD_GET_GROUP_SEQ:
            t->group_seq = ngx_atoi(res->error_str, res->error_len - 1);
            if (t->group_seq == NGX_ERROR || t->group_seq < 0) {
                ngx_log_error(NGX_LOG_WARN, t->log, 0,
                              "invalid  group seq \"%s\" ", res->error_str);
                t->group_seq = 0; /* compatible with old ns(1.3) */
            }
        }

    } else {
        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                      "tfs name server ctl message invalid");
        return NGX_ERROR;
    }

    return NGX_OK;
}