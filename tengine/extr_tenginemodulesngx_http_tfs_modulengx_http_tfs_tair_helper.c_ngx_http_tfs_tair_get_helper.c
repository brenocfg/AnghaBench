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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_tfs_tair_instance_t ;
typedef  int /*<<< orphan*/  ngx_http_tair_get_handler_pt ;
typedef  int /*<<< orphan*/  ngx_http_tair_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 

ngx_int_t
ngx_http_tfs_tair_get_helper(ngx_http_tfs_tair_instance_t *instance,
    ngx_pool_t *pool, ngx_log_t *log,
    ngx_http_tair_data_t *key, ngx_http_tair_get_handler_pt callback,
    void *data)
{
    return NGX_ERROR;
}