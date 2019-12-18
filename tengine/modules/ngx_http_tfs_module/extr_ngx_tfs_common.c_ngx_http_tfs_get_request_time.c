#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_9__ {int sec; int msec; } ;
typedef  TYPE_1__ ngx_time_t ;
typedef  int ngx_msec_int_t ;
struct TYPE_10__ {TYPE_3__* data; } ;
typedef  TYPE_2__ ngx_http_tfs_t ;
struct TYPE_11__ {int start_sec; int start_msec; } ;
typedef  TYPE_3__ ngx_http_request_t ;
struct TYPE_12__ {scalar_t__ request_time_cache; } ;
typedef  TYPE_4__ ngx_http_core_loc_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_gettimeofday (struct timeval*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int ngx_max (int,int /*<<< orphan*/ ) ; 
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