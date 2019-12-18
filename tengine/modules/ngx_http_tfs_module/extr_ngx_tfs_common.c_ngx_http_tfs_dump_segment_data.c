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
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_4__ {int /*<<< orphan*/  crc; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  file_id; int /*<<< orphan*/  block_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  oper_size; int /*<<< orphan*/  oper_offset; TYPE_1__ segment_info; } ;
typedef  TYPE_2__ ngx_http_tfs_segment_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_log_debug7 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ngx_http_tfs_dump_segment_data(ngx_http_tfs_segment_data_t *segment,
    ngx_log_t *log)
{
    ngx_log_debug7(NGX_LOG_DEBUG_HTTP, log, 0,
                   "=========dump segment data=========\n"
                   "block id: %uD, file id: %uL, "
                   "offset: %L, size: %uL, crc: %uD, "
                   "oper_offset: %uD, oper_size: %uL",
                   segment->segment_info.block_id,
                   segment->segment_info.file_id,
                   segment->segment_info.offset,
                   segment->segment_info.size,
                   segment->segment_info.crc,
                   segment->oper_offset,
                   segment->oper_size);
}