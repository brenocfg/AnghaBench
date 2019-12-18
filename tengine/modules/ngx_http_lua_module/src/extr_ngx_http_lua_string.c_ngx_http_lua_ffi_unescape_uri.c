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
 int /*<<< orphan*/  NGX_UNESCAPE_URI_COMPONENT ; 
 int /*<<< orphan*/  ngx_http_lua_unescape_uri (int /*<<< orphan*/ **,int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ) ; 

size_t
ngx_http_lua_ffi_unescape_uri(const u_char *src, size_t len, u_char *dst)
{
    u_char      *p = dst;

    ngx_http_lua_unescape_uri(&p, (u_char **) &src, len,
                              NGX_UNESCAPE_URI_COMPONENT);
    return p - dst;
}