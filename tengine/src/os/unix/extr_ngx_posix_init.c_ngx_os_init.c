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
typedef  int ngx_uint_t ;
struct TYPE_5__ {unsigned int sec; unsigned int msec; } ;
typedef  TYPE_1__ ngx_time_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {scalar_t__ rlim_cur; } ;

/* Variables and functions */
 long NGX_CPU_CACHE_LINE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int /*<<< orphan*/  _SC_LEVEL1_DCACHE_LINESIZE ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  errno ; 
 int getpagesize () ; 
 int getrlimit (int /*<<< orphan*/ ,TYPE_2__*) ; 
 long ngx_cacheline_size ; 
 int /*<<< orphan*/  ngx_cpuinfo () ; 
 int ngx_inherited_nonblocking ; 
 scalar_t__ ngx_init_setproctitle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ngx_max_sockets ; 
 int ngx_ncpu ; 
 scalar_t__ ngx_os_specific_init (int /*<<< orphan*/ *) ; 
 int ngx_pagesize ; 
 int /*<<< orphan*/  ngx_pagesize_shift ; 
 scalar_t__ ngx_pid ; 
 TYPE_1__* ngx_timeofday () ; 
 TYPE_2__ rlmt ; 
 int /*<<< orphan*/  srandom (unsigned int) ; 
 void* sysconf (int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_os_init(ngx_log_t *log)
{
    ngx_time_t  *tp;
    ngx_uint_t   n;
#if (NGX_HAVE_LEVEL1_DCACHE_LINESIZE)
    long         size;
#endif

#if (NGX_HAVE_OS_SPECIFIC_INIT)
    if (ngx_os_specific_init(log) != NGX_OK) {
        return NGX_ERROR;
    }
#endif

    if (ngx_init_setproctitle(log) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_pagesize = getpagesize();
    ngx_cacheline_size = NGX_CPU_CACHE_LINE;

    for (n = ngx_pagesize; n >>= 1; ngx_pagesize_shift++) { /* void */ }

#if (NGX_HAVE_SC_NPROCESSORS_ONLN)
    if (ngx_ncpu == 0) {
        ngx_ncpu = sysconf(_SC_NPROCESSORS_ONLN);
    }
#endif

    if (ngx_ncpu < 1) {
        ngx_ncpu = 1;
    }

#if (NGX_HAVE_LEVEL1_DCACHE_LINESIZE)
    size = sysconf(_SC_LEVEL1_DCACHE_LINESIZE);
    if (size > 0) {
        ngx_cacheline_size = size;
    }
#endif

    ngx_cpuinfo();

    if (getrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
        ngx_log_error(NGX_LOG_ALERT, log, errno,
                      "getrlimit(RLIMIT_NOFILE) failed");
        return NGX_ERROR;
    }

    ngx_max_sockets = (ngx_int_t) rlmt.rlim_cur;

#if (NGX_HAVE_INHERITED_NONBLOCK || NGX_HAVE_ACCEPT4)
    ngx_inherited_nonblocking = 1;
#else
    ngx_inherited_nonblocking = 0;
#endif

    tp = ngx_timeofday();
    srandom(((unsigned) ngx_pid << 16) ^ tp->sec ^ tp->msec);

    return NGX_OK;
}