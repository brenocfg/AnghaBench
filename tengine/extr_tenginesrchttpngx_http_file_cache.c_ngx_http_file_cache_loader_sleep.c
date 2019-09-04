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
struct TYPE_3__ {scalar_t__ files; int /*<<< orphan*/  last; int /*<<< orphan*/  loader_sleep; } ;
typedef  TYPE_1__ ngx_http_file_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_current_msec ; 
 int /*<<< orphan*/  ngx_msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_time_update () ; 

__attribute__((used)) static void
ngx_http_file_cache_loader_sleep(ngx_http_file_cache_t *cache)
{
    ngx_msleep(cache->loader_sleep);

    ngx_time_update();

    cache->last = ngx_current_msec;
    cache->files = 0;
}