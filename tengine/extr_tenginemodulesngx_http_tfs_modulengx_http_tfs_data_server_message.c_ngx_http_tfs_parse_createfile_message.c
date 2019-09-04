#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  seq_id; } ;
struct TYPE_14__ {TYPE_1__ file; } ;
struct TYPE_16__ {TYPE_10__ fsname; int /*<<< orphan*/  file_suffix; } ;
struct TYPE_18__ {TYPE_2__ r_ctx; int /*<<< orphan*/  log; TYPE_6__* tfs_peer; scalar_t__ header; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_17__ {int /*<<< orphan*/  file_id; } ;
struct TYPE_19__ {int /*<<< orphan*/  write_file_number; TYPE_3__ segment_info; } ;
typedef  TYPE_5__ ngx_http_tfs_segment_data_t ;
struct TYPE_23__ {scalar_t__ pos; } ;
struct TYPE_20__ {TYPE_9__ body_buffer; } ;
typedef  TYPE_6__ ngx_http_tfs_peer_connection_t ;
struct TYPE_21__ {int type; } ;
typedef  TYPE_7__ ngx_http_tfs_header_t ;
struct TYPE_22__ {int /*<<< orphan*/  file_number; int /*<<< orphan*/  file_id; } ;
typedef  TYPE_8__ ngx_http_tfs_ds_cf_reponse_t ;

/* Variables and functions */
#define  NGX_HTTP_TFS_STATUS_MESSAGE 128 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_raw_fsname_get_file_id (TYPE_10__) ; 
 int /*<<< orphan*/  ngx_http_tfs_raw_fsname_set_suffix (TYPE_10__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_tfs_status_message (TYPE_9__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_tfs_parse_createfile_message(ngx_http_tfs_t *t,
    ngx_http_tfs_segment_data_t *segment_data)
{
    uint16_t                         type;
    ngx_str_t                        action;
    ngx_http_tfs_header_t           *header;
    ngx_http_tfs_ds_cf_reponse_t    *resp;
    ngx_http_tfs_peer_connection_t  *tp;

    header = (ngx_http_tfs_header_t *) t->header;
    tp = t->tfs_peer;
    type = header->type;

    switch (type) {

    case NGX_HTTP_TFS_STATUS_MESSAGE:
        ngx_str_set(&action, "create file(data server)");
        return ngx_http_tfs_status_message(&tp->body_buffer, &action, t->log);
    }

    resp = (ngx_http_tfs_ds_cf_reponse_t *) tp->body_buffer.pos;

    t->r_ctx.fsname.file.seq_id = resp->file_id;
    ngx_http_tfs_raw_fsname_set_suffix((&t->r_ctx.fsname),
                                       (&t->r_ctx.file_suffix));
    segment_data->segment_info.file_id =
                          ngx_http_tfs_raw_fsname_get_file_id(t->r_ctx.fsname);
    segment_data->write_file_number = resp->file_number;

    ngx_log_debug3(NGX_LOG_DEBUG_HTTP, t->log, 0,
                   "create file success, seq id: %uD, "
                   "file id: %uL, file number: %uL",
                   t->r_ctx.fsname.file.seq_id,
                   segment_data->segment_info.file_id,
                   segment_data->write_file_number);

    return NGX_OK;
}