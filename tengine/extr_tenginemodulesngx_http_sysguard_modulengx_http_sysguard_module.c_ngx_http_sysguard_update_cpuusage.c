#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int time_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_4__ {int usr; int nice; int sys; int iowait; int irq; int softirq; int idle; } ;
typedef  TYPE_1__ ngx_cpuinfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int ngx_http_sysguard_cached_cpuusage ; 
 int ngx_http_sysguard_cached_cpuusage_exptime ; 
 TYPE_1__ ngx_http_sysguard_cached_cur_cputime ; 
 TYPE_1__ ngx_http_sysguard_cached_pre_cputime ; 
 int ngx_time () ; 

__attribute__((used)) static ngx_int_t
ngx_http_sysguard_update_cpuusage(ngx_http_request_t *r, time_t exptime)
{
    time_t         cpu_diff, total_diff;
    ngx_cpuinfo_t  pre, cur;

    pre = ngx_http_sysguard_cached_pre_cputime;
    cur = ngx_http_sysguard_cached_cur_cputime;

    ngx_http_sysguard_cached_cpuusage_exptime = ngx_time() + exptime;

    cpu_diff = (cur.usr + cur.nice + cur.sys) - (pre.usr + pre.nice + pre.sys);

    total_diff = (cur.usr + cur.nice + cur.sys + cur.iowait + cur.irq
                 + cur.softirq + cur.idle)
                 - (pre.usr + pre.nice + pre.sys + pre.iowait + pre.irq
                 + pre.softirq + pre.idle);

    if (total_diff == 0) {
        total_diff = 1;
    }

    ngx_http_sysguard_cached_cpuusage = cpu_diff * 100 * 100 / total_diff;

    return NGX_OK;
}