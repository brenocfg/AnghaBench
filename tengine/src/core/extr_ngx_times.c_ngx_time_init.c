#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int len; } ;
struct TYPE_9__ {int len; } ;
struct TYPE_8__ {int len; } ;
struct TYPE_7__ {int len; } ;
struct TYPE_6__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cached_http_log_tm ; 
 int /*<<< orphan*/ * cached_time ; 
 TYPE_5__ ngx_cached_err_log_time ; 
 TYPE_4__ ngx_cached_http_log_iso8601 ; 
 TYPE_3__ ngx_cached_http_log_time ; 
 TYPE_2__ ngx_cached_http_time ; 
 TYPE_1__ ngx_cached_syslog_time ; 
 int /*<<< orphan*/ * ngx_cached_time ; 
 int /*<<< orphan*/ * ngx_cached_tm ; 
 int /*<<< orphan*/  ngx_time_update () ; 

void
ngx_time_init(void)
{
    ngx_cached_err_log_time.len = sizeof("1970/09/28 12:00:00") - 1;
    ngx_cached_http_time.len = sizeof("Mon, 28 Sep 1970 06:00:00 GMT") - 1;
    ngx_cached_http_log_time.len = sizeof("28/Sep/1970:12:00:00 +0600") - 1;
    ngx_cached_http_log_iso8601.len = sizeof("1970-09-28T12:00:00+06:00") - 1;
    ngx_cached_syslog_time.len = sizeof("Sep 28 12:00:00") - 1;

    ngx_cached_time = &cached_time[0];
#if (T_NGX_RET_CACHE)
    ngx_cached_tm = &cached_http_log_tm[0];
#endif

    ngx_time_update();
}