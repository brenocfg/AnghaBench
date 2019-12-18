#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  crc; int /*<<< orphan*/  flag; int /*<<< orphan*/  create_time; int /*<<< orphan*/  modify_time; int /*<<< orphan*/  u_size; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ ngx_http_tfs_raw_file_stat_t ;
struct TYPE_6__ {int /*<<< orphan*/  crc; int /*<<< orphan*/  flag; int /*<<< orphan*/  create_time; int /*<<< orphan*/  modify_time; int /*<<< orphan*/  u_size; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ ngx_http_tfs_raw_file_info_t ;

/* Variables and functions */

void
ngx_http_tfs_wrap_raw_file_info(ngx_http_tfs_raw_file_info_t *file_info,
    ngx_http_tfs_raw_file_stat_t *file_stat)
{
    if (file_info != NULL && file_stat != NULL) {
        file_stat->id = file_info->id;
        file_stat->offset = file_info->offset;
        file_stat->size = file_info->size;
        file_stat->u_size = file_info->u_size;
        file_stat->modify_time = file_info->modify_time;
        file_stat->create_time = file_info->create_time;
        file_stat->flag = file_info->flag;
        file_stat->crc = file_info->crc;
    }
}