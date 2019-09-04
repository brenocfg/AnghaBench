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
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_conf_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_stream_top_filter ; 
 int /*<<< orphan*/  ngx_stream_write_filter ; 

__attribute__((used)) static ngx_int_t
ngx_stream_write_filter_init(ngx_conf_t *cf)
{
    ngx_stream_top_filter = ngx_stream_write_filter;

    return NGX_OK;
}