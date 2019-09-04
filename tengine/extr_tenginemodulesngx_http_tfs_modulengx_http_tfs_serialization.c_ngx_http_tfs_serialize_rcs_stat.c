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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_int_t ;
struct TYPE_4__ {int oper_app_id; int oper_type; int /*<<< orphan*/  oper_succ; int /*<<< orphan*/  oper_rt; int /*<<< orphan*/  oper_size; int /*<<< orphan*/  oper_times; } ;
typedef  TYPE_1__ ngx_http_tfs_stat_rcs_t ;
struct TYPE_5__ {TYPE_1__* stat_rcs; } ;
typedef  TYPE_2__ ngx_http_tfs_rcs_info_t ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 size_t NGX_HTTP_TFS_OPER_COUNT ; 
 size_t NGX_OK ; 

ngx_int_t
ngx_http_tfs_serialize_rcs_stat(u_char **p,
    ngx_http_tfs_rcs_info_t  *rc_info, ngx_int_t *count)
{
    ngx_int_t                    i;
    ngx_http_tfs_stat_rcs_t     *stat_rcs;

    if (p == NULL || rc_info == NULL || count == NULL) {
        return NGX_ERROR;
    }

    *count = 0;
    stat_rcs = rc_info->stat_rcs;

    for (i = 0; i < NGX_HTTP_TFS_OPER_COUNT; ++i) {
        if (stat_rcs[i].oper_app_id == 0) {
            continue;
        }

        *((uint32_t *)*p) = (stat_rcs[i].oper_app_id << 16) | stat_rcs[i].oper_type;
        (*p) += sizeof(uint32_t);

        *((uint32_t *)*p) = (stat_rcs[i].oper_app_id << 16) | stat_rcs[i].oper_type;
        (*p) += sizeof(uint32_t);
        *((uint64_t *)*p) = stat_rcs[i].oper_times;
        (*p) += sizeof(uint64_t);
        *((uint64_t *)*p) = stat_rcs[i].oper_size;
        (*p) += sizeof(uint64_t);
        *((uint64_t *)*p) = stat_rcs[i].oper_rt;
        (*p) += sizeof(uint64_t);
        *((uint64_t *)*p) = stat_rcs[i].oper_succ;
        (*p) += sizeof(uint64_t);

        ++(*count);
    }

    return NGX_OK;
}