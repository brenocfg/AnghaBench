#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_7__ {scalar_t__ offset; } ;
struct TYPE_8__ {scalar_t__ oper_size; TYPE_1__ segment_info; } ;
typedef  TYPE_2__ ngx_http_tfs_segment_data_t ;
struct TYPE_9__ {scalar_t__ segment_count; scalar_t__ file_offset; scalar_t__ left_length; int /*<<< orphan*/  still_have; TYPE_2__* segment_data; } ;
typedef  TYPE_3__ ngx_http_tfs_file_t ;
struct TYPE_10__ {scalar_t__ offset; scalar_t__ length; } ;
typedef  TYPE_4__ ngx_http_tfs_file_hole_info_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DONE ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 
 int /*<<< orphan*/  NGX_OK ; 
 TYPE_4__* ngx_array_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ ngx_min (scalar_t__,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_check_file_hole(ngx_http_tfs_file_t *file, ngx_array_t *file_holes, ngx_log_t *log)
{
    int64_t                         curr_length;
    uint32_t                        segment_count, i;
    ngx_http_tfs_segment_data_t    *segment_data;
    ngx_http_tfs_file_hole_info_t  *file_hole_info;

    if (file == NULL || file_holes == NULL) {
        return NGX_ERROR;
    }

    segment_data = file->segment_data;
    if (segment_data != NULL) {
        segment_count = file->segment_count;
        for (i = 0; i < segment_count; i++, segment_data++) {
            if (file->file_offset < segment_data->segment_info.offset) {
                curr_length = ngx_min(file->left_length,
                    (uint64_t)(segment_data->segment_info.offset - file->file_offset));
                file_hole_info = ngx_array_push(file_holes);
                if (file_hole_info == NULL) {
                    return NGX_ERROR;
                }

                file_hole_info->offset = file->file_offset;
                file_hole_info->length = curr_length;

                ngx_log_error(NGX_LOG_DEBUG, log, 0,
                              "find file hole, offset: %uL, length: %uL",
                              file_hole_info->offset, file_hole_info->length);

                file->file_offset += curr_length;
                file->left_length -= curr_length;
                if (file->left_length == 0) {
                    break;
                }
            }
            file->file_offset += segment_data->oper_size;
            file->left_length -= segment_data->oper_size;
            if (file->left_length == 0) {
                break;
            }
        }
    }

    if (!file->still_have) {
        /* left is all file hole(beyond last segment) */
        if (file->left_length > 0) {
            file_hole_info = ngx_array_push(file_holes);
            if (file_hole_info == NULL) {
                return NGX_ERROR;
            }

            file_hole_info->offset = file->file_offset;
            file_hole_info->length = file->left_length;

            ngx_log_error(NGX_LOG_DEBUG, log, 0,
                          "find file hole, offset: %uL, length: %uL",
                          file_hole_info->offset, file_hole_info->length);
            file->file_offset += file->left_length;
            file->left_length = 0;
        }

        return NGX_DONE;
    }

    return NGX_OK;
}