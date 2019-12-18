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
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_tfs_remote_block_cache_dummy_handler(ngx_int_t rc, void *data)
{
    ngx_destroy_pool((ngx_pool_t *)data);
}