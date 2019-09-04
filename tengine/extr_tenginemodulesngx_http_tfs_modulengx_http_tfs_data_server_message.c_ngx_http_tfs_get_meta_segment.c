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
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  suffix; int /*<<< orphan*/  seq_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_15__ {TYPE_2__ file; } ;
struct TYPE_11__ {TYPE_7__ fsname; } ;
struct TYPE_9__ {int segment_count; TYPE_6__* segment_data; } ;
struct TYPE_12__ {TYPE_3__ r_ctx; int /*<<< orphan*/  log; TYPE_1__ file; int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_13__ {int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; scalar_t__ size; scalar_t__ offset; } ;
typedef  TYPE_5__ ngx_http_tfs_segment_info_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_segment_data_t ;
struct TYPE_14__ {TYPE_5__ segment_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_tfs_raw_fsname_get_file_id (TYPE_7__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_http_tfs_get_meta_segment(ngx_http_tfs_t *t)
{
    ngx_http_tfs_segment_info_t  *segment_info;

    t->file.segment_count = 1;

    if (t->file.segment_data == NULL) {
        t->file.segment_data = ngx_pcalloc(t->pool,
                                           sizeof(ngx_http_tfs_segment_data_t));
        if (t->file.segment_data == NULL) {
            return NGX_ERROR;
        }
    }

    segment_info = &t->file.segment_data[0].segment_info;
    segment_info->block_id = t->r_ctx.fsname.file.block_id;
    segment_info->file_id =
                           ngx_http_tfs_raw_fsname_get_file_id(t->r_ctx.fsname);
    segment_info->offset = 0;
    segment_info->size = 0;

    ngx_log_error(NGX_LOG_INFO, t->log, 0,
                  "meta segment: block_id: %uD, fileid: %uL, "
                  "seq_id: %uD, suffix: %uD",
                  segment_info->block_id,
                  segment_info->file_id,
                  t->r_ctx.fsname.file.seq_id,
                  t->r_ctx.fsname.file.suffix);

    return NGX_OK;
}