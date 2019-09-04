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
struct TYPE_3__ {int resource_count; int wait_count; } ;
typedef  TYPE_1__ ngx_http_lua_sema_t ;

/* Variables and functions */

int
ngx_http_lua_ffi_sema_count(ngx_http_lua_sema_t *sem)
{
    return sem->resource_count - sem->wait_count;
}