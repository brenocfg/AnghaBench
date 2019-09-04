#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ngx_int_t ;

/* Variables and functions */
 scalar_t__ ngx_exiting ; 
 int /*<<< orphan*/  ngx_http_upstream_check_clear_all_events () ; 
 scalar_t__ ngx_quit ; 
 scalar_t__ ngx_terminate ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_need_exit()
{
    if (ngx_terminate || ngx_exiting || ngx_quit) {
        ngx_http_upstream_check_clear_all_events();
        return 1;
    }

    return 0;
}