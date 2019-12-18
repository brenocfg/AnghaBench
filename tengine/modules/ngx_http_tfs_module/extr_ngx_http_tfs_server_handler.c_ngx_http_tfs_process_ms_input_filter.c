#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  log; scalar_t__ header; } ;
typedef  TYPE_1__ ngx_http_tfs_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_2__ ngx_http_tfs_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_http_tfs_process_ms_input_filter(ngx_http_tfs_t *t)
{
    ngx_http_tfs_header_t  *header;

    header = (ngx_http_tfs_header_t *) t->header;
    t->length = header->len;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, t->log, 0,
                   "ls dir len is %O",
                   t->length);

    return NGX_OK;
}