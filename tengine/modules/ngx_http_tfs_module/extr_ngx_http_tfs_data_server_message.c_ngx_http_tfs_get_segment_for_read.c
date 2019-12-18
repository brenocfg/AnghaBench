#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int segment_count; TYPE_7__* segment_data; scalar_t__ left_length; scalar_t__ segment_index; } ;
struct TYPE_14__ {scalar_t__ size; scalar_t__ offset; } ;
struct TYPE_16__ {TYPE_3__ file; int /*<<< orphan*/  log; TYPE_2__ r_ctx; int /*<<< orphan*/  pool; TYPE_6__* seg_head; TYPE_1__* meta_segment_data; } ;
typedef  TYPE_4__ ngx_http_tfs_t ;
struct TYPE_17__ {scalar_t__ offset; scalar_t__ size; } ;
typedef  TYPE_5__ ngx_http_tfs_segment_info_t ;
struct TYPE_18__ {scalar_t__ size; int count; } ;
typedef  TYPE_6__ ngx_http_tfs_segment_head_t ;
struct TYPE_19__ {scalar_t__ oper_size; scalar_t__ oper_offset; TYPE_5__ segment_info; } ;
typedef  TYPE_7__ ngx_http_tfs_segment_data_t ;
struct TYPE_20__ {int /*<<< orphan*/ * last; scalar_t__ pos; } ;
typedef  TYPE_8__ ngx_buf_t ;
typedef  size_t int32_t ;
struct TYPE_13__ {TYPE_8__* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_MAX_SIZE ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int ngx_buf_size (TYPE_8__*) ; 
 size_t ngx_http_tfs_find_segment (int,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ ngx_min (scalar_t__,scalar_t__) ; 
 TYPE_7__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

ngx_int_t
ngx_http_tfs_get_segment_for_read(ngx_http_tfs_t *t)
{
    uint32_t                      buf_size, seg_count, max_seg_count, i;
    uint64_t                      start_offset, end_offset, data_size;
    int32_t                       start_seg, end_seg;
    ngx_buf_t                    *b;
    ngx_http_tfs_segment_info_t  *seg_info;
    ngx_http_tfs_segment_data_t  *first_segment, *last_segment;

    if (t->meta_segment_data == NULL) {
        return NGX_ERROR;
    }
    b = t->meta_segment_data->buf;
    if (b == NULL) {
        return NGX_ERROR;
    }

    buf_size = ngx_buf_size(b);
    if (buf_size < (sizeof(ngx_http_tfs_segment_head_t) +
                    sizeof(ngx_http_tfs_segment_info_t)))
    {
        return NGX_ERROR;
    }

    t->seg_head = (ngx_http_tfs_segment_head_t *)(b->pos);
    seg_info = (ngx_http_tfs_segment_info_t *)
                (b->pos + sizeof(ngx_http_tfs_segment_head_t));

    if (t->r_ctx.size == NGX_HTTP_TFS_MAX_SIZE) {
        data_size = t->seg_head->size;

    } else {
        data_size = t->r_ctx.size;
    }

    start_offset = t->r_ctx.offset;
    end_offset = start_offset + data_size;
    if (start_offset >= t->seg_head->size) {
        return NGX_DONE;
    }

    /* find out the segment we should start with */
    seg_count = t->seg_head->count;
    max_seg_count = (b->last - (u_char *) seg_info)
                     / sizeof(ngx_http_tfs_segment_info_t);
    if (t->seg_head->count > max_seg_count) {
        ngx_log_error(NGX_LOG_ERR, t->log, 0,
                      "seg_count in seg_head larger than max seg_count, "
                      "%uD > %uD, seg_head may be corrupted.",
                      t->seg_head->count, max_seg_count);
        seg_count = max_seg_count - 1;
    }
    start_seg = ngx_http_tfs_find_segment(seg_count, seg_info, start_offset);
    if (start_seg < 0) {
        start_seg = 0 - start_seg - 1;
        if (((uint64_t) seg_info[start_seg].offset + seg_info[start_seg].size)
            <= start_offset)
        {
            return NGX_ERROR;
        }
    }

    /* find out the last segment */
    end_seg = ngx_http_tfs_find_segment(seg_count, seg_info, end_offset);
    if (end_seg > 0) {
        end_seg -= 1;

    } else if (end_seg < 0) {
        end_seg = 0 - end_seg - 1;

    } else {
        return NGX_ERROR;
    }

    seg_count = end_seg - start_seg + 1;

    /* alloc segment_data */
    t->file.segment_data = ngx_pcalloc(t->pool,
                               sizeof(ngx_http_tfs_segment_data_t) * seg_count);
    if (t->file.segment_data == NULL) {
        return NGX_ERROR;
    }

    t->file.segment_index = 0;
    t->file.segment_count = seg_count;
    t->file.left_length = data_size;

    for (i = 0; start_seg <= end_seg; i++, start_seg++) {
        t->file.segment_data[i].segment_info = seg_info[start_seg];
        t->file.segment_data[i].oper_size =
                                      t->file.segment_data[i].segment_info.size;
    }

    /* first segment's oper_offset and oper_size are special for pread */
    first_segment = &t->file.segment_data[0];
    first_segment->oper_offset = t->r_ctx.offset;
    if (first_segment->segment_info.offset > 0) {
        first_segment->oper_offset -= first_segment->segment_info.offset;
    }
    first_segment->oper_size =
        first_segment->segment_info.size - first_segment->oper_offset;

    /*
     * last segment's oper_size is special,
     * notice that last_segment maybe the same as first_semgnt
     */
    last_segment = &t->file.segment_data[seg_count - 1];
    last_segment->oper_size = ngx_min((end_offset
                                       - (last_segment->segment_info.offset
                                          + last_segment->oper_offset)),
                                      last_segment->segment_info.size);

#if (NGX_DEBUG)
    for (i = 0; i < seg_count; i++) {
        ngx_log_debug3(NGX_LOG_DEBUG_HTTP, t->log, 0,
                      "segment index: %d, oper_offset: %uD, oper_size: %uD",
                      i, t->file.segment_data[i].oper_offset,
                      t->file.segment_data[i].oper_size);
    }
#endif

    return NGX_OK;
}