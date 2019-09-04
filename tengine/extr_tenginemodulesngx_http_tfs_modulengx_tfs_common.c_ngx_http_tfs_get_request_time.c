#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int sec; scalar_t__ msec; } ;
typedef  TYPE_1__ ngx_time_t ;
typedef  scalar_t__ ngx_msec_int_t ;
struct TYPE_7__ {TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
struct TYPE_8__ {int start_sec; scalar_t__ start_msec; } ;
typedef  TYPE_3__ ngx_http_request_t ;

/* Variables and functions */
 scalar_t__ ngx_max (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* ngx_timeofday () ; 

ngx_msec_int_t
ngx_http_tfs_get_request_time(ngx_http_tfs_t *t)
{
    ngx_time_t                *tp;
    ngx_msec_int_t             ms;
    ngx_http_request_t        *r;
#if (T_NGX_RET_CACHE)
    struct timeval             tv;
    ngx_http_core_loc_conf_t  *clcf;
#endif

    r = t->data;

#if (T_NGX_RET_CACHE)
    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
    if (clcf->request_time_cache) {
        tp = ngx_timeofday();
        ms = (ngx_msec_int_t)
                 ((tp->sec - r->start_sec) * 1000 + (tp->msec - r->start_msec));
    } else {
        ngx_gettimeofday(&tv);
        ms = (tv.tv_sec - r->start_sec) * 1000
                 + (tv.tv_usec / 1000 - r->start_msec);
    }

#else 

    tp = ngx_timeofday();
    ms = (ngx_msec_int_t)
             ((tp->sec - r->start_sec) * 1000 + (tp->msec - r->start_msec));
#endif

    ms = ngx_max(ms, 0);

    return ms;
}