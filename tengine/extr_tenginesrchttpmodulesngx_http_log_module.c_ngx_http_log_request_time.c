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
typedef  int /*<<< orphan*/  u_char ;
typedef  int time_t ;
struct TYPE_5__ {int sec; scalar_t__ msec; } ;
typedef  TYPE_1__ ngx_time_t ;
typedef  int ngx_msec_int_t ;
struct TYPE_6__ {int start_sec; scalar_t__ start_msec; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_log_op_t ;

/* Variables and functions */
 int ngx_max (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int,int) ; 
 TYPE_1__* ngx_timeofday () ; 

__attribute__((used)) static u_char *
ngx_http_log_request_time(ngx_http_request_t *r, u_char *buf,
    ngx_http_log_op_t *op)
{
    ngx_time_t      *tp;
    ngx_msec_int_t   ms;

#if (T_NGX_RET_CACHE)
    struct timeval             tv;
    ngx_http_core_loc_conf_t  *clcf;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
    if (clcf->request_time_cache) {
        tp = ngx_timeofday();
        ms = (ngx_msec_int_t)
                 ((tp->sec - r->start_sec) * 1000 + (tp->msec - r->start_msec));

    } else {
        ngx_gettimeofday(&tv);
        ms = (ngx_msec_int_t)
             ((tv.tv_sec - r->start_sec) * 1000
              + (tv.tv_usec / 1000 - r->start_msec));
    }

#else
    tp = ngx_timeofday();

    ms = (ngx_msec_int_t)
             ((tp->sec - r->start_sec) * 1000 + (tp->msec - r->start_msec));
#endif

    ms = ngx_max(ms, 0);

    return ngx_sprintf(buf, "%T.%03M", (time_t) ms / 1000, ms % 1000);
}