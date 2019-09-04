#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_10__ {TYPE_1__ stat_info; } ;
typedef  TYPE_3__ ngx_http_tfs_t ;
struct TYPE_11__ {scalar_t__ app_id; TYPE_2__* stat_rcs; } ;
typedef  TYPE_4__ ngx_http_tfs_rcs_info_t ;
typedef  scalar_t__ ngx_http_tfs_oper_type_e ;
typedef  size_t int32_t ;
struct TYPE_9__ {scalar_t__ oper_app_id; int /*<<< orphan*/  oper_rt; int /*<<< orphan*/  oper_succ; int /*<<< orphan*/  oper_size; int /*<<< orphan*/  oper_times; scalar_t__ oper_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 scalar_t__ NGX_HTTP_TFS_OPER_COUNT ; 
 int /*<<< orphan*/  NGX_OK ; 
 scalar_t__ ngx_http_tfs_get_request_time (TYPE_3__*) ; 

ngx_int_t
ngx_http_tfs_rcs_stat_update(ngx_http_tfs_t *t,
    ngx_http_tfs_rcs_info_t *rc_info, ngx_http_tfs_oper_type_e oper_type)
{
    if (t == NULL || rc_info ==  NULL || oper_type >= NGX_HTTP_TFS_OPER_COUNT) {
        return NGX_ERROR;
    }

    int32_t index = oper_type;

    if (rc_info->stat_rcs[index].oper_app_id == 0 ) {
        rc_info->stat_rcs[index].oper_app_id = rc_info->app_id;
        rc_info->stat_rcs[index].oper_type = oper_type;
    }

    ++rc_info->stat_rcs[index].oper_times;
    rc_info->stat_rcs[index].oper_size += t->stat_info.size;
    ++rc_info->stat_rcs[index].oper_succ;
    rc_info->stat_rcs[index].oper_rt += ngx_http_tfs_get_request_time(t);

    return NGX_OK;
}