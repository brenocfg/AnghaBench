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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int /*<<< orphan*/ * ngx_http_cookie_time (int /*<<< orphan*/ *,long) ; 

int
ngx_http_lua_ffi_cookie_time(u_char *buf, long t)
{
    u_char                              *p;

    p = ngx_http_cookie_time(buf, t);
    return p - buf;
}