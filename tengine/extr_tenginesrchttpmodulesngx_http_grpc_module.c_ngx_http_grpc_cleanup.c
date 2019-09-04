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

/* Variables and functions */

__attribute__((used)) static void
ngx_http_grpc_cleanup(void *data)
{
#if 0
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "grpc cleanup");
#endif
    return;
}