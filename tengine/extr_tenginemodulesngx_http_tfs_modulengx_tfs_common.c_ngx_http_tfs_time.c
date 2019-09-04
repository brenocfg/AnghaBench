#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  time_t ;
struct TYPE_3__ {size_t ngx_tm_wday; int ngx_tm_mon; int /*<<< orphan*/  ngx_tm_sec; int /*<<< orphan*/  ngx_tm_min; int /*<<< orphan*/  ngx_tm_hour; int /*<<< orphan*/  ngx_tm_year; int /*<<< orphan*/  ngx_tm_mday; } ;
typedef  TYPE_1__ ngx_tm_t ;

/* Variables and functions */
 int /*<<< orphan*/ * months ; 
 int /*<<< orphan*/  ngx_gmtime (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * week ; 

u_char *
ngx_http_tfs_time(u_char *buf, time_t t)
{
    ngx_tm_t  tm;

    ngx_gmtime(t, &tm);

    return ngx_sprintf(buf, "%s, %02d %s %4d %02d:%02d:%02d GMT",
                       week[tm.ngx_tm_wday],
                       tm.ngx_tm_mday,
                       months[tm.ngx_tm_mon - 1],
                       tm.ngx_tm_year,
                       tm.ngx_tm_hour,
                       tm.ngx_tm_min,
                       tm.ngx_tm_sec);
}